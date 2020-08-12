#include "stdafx.h"
#include "ShadowMap.h"
#include "graphics/SkinModelShaderConst.h"

ShadowMap::ShadowMap()
{
	Init();
}

ShadowMap::~ShadowMap()
{
	Release();
}

void ShadowMap::Release()
{
	//解放
	for (auto& rt : m_KshadowMapRT) {
		rt.Release();
	}
}

void ShadowMap::Init()
{
	//一応解放
	Release();

	//カスケードシャドウのライトカメラの位置
	m_lightHieght = 2000.0f;

	//カスケードシャドウマップの範囲
	//恐らく処理が早いから左シフト
	//ここでシャドウの解像度が決まるよ！
	int wh[][2] = {
		//そのままの範囲
		{shadowMapWidth, shadowMapHeight},
		//縦を右シフト1なので縦の値が半分に
		{shadowMapWidth, shadowMapHeight >> 2},
		//横を右シフト1、縦が右シフト1なので両方半分に
		{shadowMapWidth >> 2, shadowMapHeight >> 2}
	};

	//シャドウマップ用のレンダリングターゲットを個数分作成
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		m_KshadowMapRT[i].Create(
			wh[i][0],
			wh[i][1],
			DXGI_FORMAT_R32_FLOAT
		);
		//pivot的な奴？
		//m_shadowCbEntity.texOffset[i].x = 1.0f / wh[i][0];
		//m_shadowCbEntity.texOffset[i].y = 1.0f / wh[i][1];
	}

	//定数バッファを作成
	m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));

	//シャドウマップ用サンプラー作成
	CD3D11_DEFAULT def;
	CD3D11_SAMPLER_DESC desc(def);

	//テクスチャを線形補間
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//範囲外は指定された色に
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//範囲外のカラー設定
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;

	//サンプラーステートを作成
	m_fetchShadowMapSampler.Create(desc);
	auto a = m_fetchShadowMapSampler.GetBody();
}

CVector3 ShadowMap::CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition)
{
	/*
	この計算を自分なりに図にしたものがカスケードシャドウのファイルの中にあるので
	コードの意味が分からなくなった場合はそこを参照。
	*/

	/*
	ライトの高さ = 視錐台の中心座標.y + ライトの方向 * a
	一次方程式なので a = に直して
	a = (ライトの高さ - 視点の中心座標.y) / ライトの方向.y
	となる。
	*/
	auto alpha = (lightHeight - viewFrustomCenterPosition.y) / m_lightDirection.y;
	/*
	aを使ってライト座標を求める。
	ライトの座標 = 視錐台の中心座標 + ライトの方向 * a
	*/
	auto lightPos = viewFrustomCenterPosition + m_lightDirection * alpha;
	//ライトの位置
	return lightPos;
}

void ShadowMap::Update()
{
	//シーンをレンダリングしているカメラを使って、ライトカメラの回転を計算
	//シーンカメラの前方向取得
	auto cameraDir = g_camera3D.GetForward();
	//fabs = 絶対値  FLT_EPSLIONでfloat特有の誤差を考慮しない。
	//x,z軸が0に近いなら
	if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
		//ほぼ真上を向いてる
		return;
	}

	//ライトビュー行列の回転成分を計算
	
	//ライトビューの前方向 下向き
	CVector3 lightViewForward = m_lightDirection;
	//ライトビューの上方向
	CVector3 lightViewUp;
	if (fabsf(lightViewForward.y) > 0.999f) {
		//ほぼ真上
		lightViewUp.Cross(lightViewForward, CVector3::Right());
	}
	else {
		lightViewUp.Cross(lightViewForward, CVector3::Up());
	}
	//正規化
	lightViewUp.Normalize();

	//ライトビューの横方向
	CVector3 lightViewRight;
	lightViewRight.Cross(lightViewUp, lightViewForward);
	lightViewRight.Normalize();

	//ライトビューに回転を設定していく
	CMatrix lightViewRot;
	//ライトビューの横を設定
	lightViewRot.m[0][0] = lightViewRight.x;
	lightViewRot.m[0][1] = lightViewRight.y;
	lightViewRot.m[0][2] = lightViewRight.z;
	lightViewRot.m[0][3] = 0.0f;
	//ライトビューの上を設定
	lightViewRot.m[1][0] = lightViewUp.x;
	lightViewRot.m[1][1] = lightViewUp.y;
	lightViewRot.m[1][2] = lightViewUp.z;
	lightViewRot.m[1][3] = 0.0f;
	//ライトビューの前を設定する。
	lightViewRot.m[2][0] = lightViewForward.x;
	lightViewRot.m[2][1] = lightViewForward.y;
	lightViewRot.m[2][2] = lightViewForward.z;
	lightViewRot.m[2][3] = 0.0f;

	//視錐台を分割する比率
	float shadowAreaTbl[] = {
		2000 * 0.2f,
		2000 * 0.4f,
		2000 * 0.8f
	};

	//ライトビューの高さを計算
	float lightHeight = g_camera3D.GetTarget().y + m_lightHieght;

	//シャドウの構造体
	SShadowCb shadowCB;
	//近平面
	float nearPlaneZ = 0.0f;
	//遠平面
	float farPlaneZ;
	//メインカメラの上方向
	CVector3 cameraUp;
	//外積で上方向を計算
	cameraUp.Cross(g_camera3D.GetRight(), g_camera3D.GetForward());
	//cameraUp = g_camera3D.GetUp();

	//視錐台を分割するようにライトビュープロジェクション行列を計算
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		//遠平面を計算
		farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
		//ライトビュー
		CMatrix mLightView = CMatrix::Identity();
		//視錐台の片方ずつ(上、下)計算していくのでアングルは半分
		float halfViewAngle = g_camera3D.GetViewAngle() * 0.5f;
		//視錐台の8頂点をライト空間に変換してAABB(視錐台の中にある直方体)を求めて、正射影の幅と高さを求める。
		float w, h;
		float far_z = -1.0f;
		//8頂点
		CVector3 v[8];
		{
			//隣返が対返に対して何倍か
			float t = tan(halfViewAngle);
			//近平面と遠平面の上ベクトル
			CVector3 toUpperNear, toUpperFar;
			//対辺を求める。カスケードシャドウのtoUpper.png参照。
			//nearPlaneZが隣返
			toUpperNear = cameraUp * t * nearPlaneZ;
			toUpperFar = cameraUp * t * farPlaneZ;
			//アスペクト比を乗算
			//いままではまっすぐ前の視錐台の線のみ計算だったのが
			//ここからは縦横の情報がはいるため　詳細はaspect.pngを参照。
			t *= g_camera3D.GetAspect();
			//近平面の中央座標を計算
			//資料8vertex.pngを参照。
			auto nearPlaneCenterPos = g_camera3D.GetPosition() + cameraDir * nearPlaneZ;

			//v[0] = 視錐台の近平面で右上にある四角形の頂点。
			v[0] = nearPlaneCenterPos + g_camera3D.GetRight() * t * nearPlaneZ + toUpperNear;
			//v[1] = 視錐台の近平面で右下にある四角形の頂点
			v[1] = v[0] - toUpperNear * 2.0f;

			//v[2] = 視錐台の近平面で左上にある四角形の頂点
			v[2] = nearPlaneCenterPos + g_camera3D.GetRight() * -t * nearPlaneZ + toUpperNear;
			//v[3] = 視錐台の近平面で左下にある四角形の頂点
			v[3] = v[2] - toUpperNear * 2.0f;

			//遠平面の中央座標を計算。
			auto farPlaneCenterPos = g_camera3D.GetPosition() + cameraDir * farPlaneZ;

			//v[4] = 視錐台の遠平面で右上にある四角形の頂点
			v[4] = farPlaneCenterPos + g_camera3D.GetRight() * t * farPlaneZ + toUpperFar;
			//v[5] = 視錐台の遠平面で右下にある四角形の頂点
			v[5] = v[4] - toUpperFar * 2.0f;

			//v[6] = 視錐台の遠平面で左上にある四角形の頂点
			v[6] = farPlaneCenterPos + g_camera3D.GetRight() * -t * farPlaneZ + toUpperFar;
			//v[7] = 視錐台の遠平面で左下にある四角形の頂点
			v[7] = v[6] - toUpperFar * 2.0f;

			//ライト行列を作成
			//視錐台の真ん中を計算。
			auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCenterPos) * 0.5f;
			//ライトの位置を計算。
			auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);
			//CVector3 lightPos = { 0,2000,1000 };

			//ライトの回転
			mLightView = lightViewRot;

			//ライトの位置,回転
			mLightView.m[3][0] = lightPos.x;
			mLightView.m[3][1] = lightPos.y;
			mLightView.m[3][2] = lightPos.z;
			mLightView.m[3][3] = 1.0f;

			//ライトビュー(ライト座標軸）完成
			//逆行列うんぬんかぬん忘れている場合はGameProgに解説あり。
			mLightView.Inverse(mLightView);

			//視錐台を構成する８頂点の計算ができたので、ライト空間に変換して、AABBを求める。
			//最大頂点座標
			CVector3 vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
			//最小頂点座標
			CVector3 vMin = { FLT_MAX,FLT_MAX ,FLT_MAX };

			//8頂点をライトの座標軸に変換する。
			for (auto & vInLight : v) {
				mLightView.Mul(vInLight);
				vMax.Max(vInLight);
				vMin.Min(vInLight);
			}
			//ビューの幅と高さを求める。
			w = vMax.x - vMin.x;
			h = vMax.y - vMin.y;
			far_z = vMax.z;
		}
		//プロジェクション行列
		CMatrix proj;
		//作成
		proj.MakeOrthoProjectionMatrix(
			w,
			h,
			far_z / 100.0f,
			far_z
		);
		m_lightViewMatrix[i] = mLightView;
		m_lightProjMatirx[i] = proj;
		//ライト座標軸に変換
		m_LVPMatrix[i] = mLightView * proj;
		//エンティティに積む
		m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
		//どこまで影を落とすか(きわきわだと変な境界が発生するので少し狭める。)
		m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ * 0.8f;
		//次の近平面は今の遠平面。
		nearPlaneZ = farPlaneZ;
	}
}

void ShadowMap::BiginRender()
{
	//デバコン取得
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
	//RTVとDSVのバックアップ
	dc->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);

	//ビューポート
	viewport = 1;
	//ビューポートのバックアップ
	dc->RSGetViewports(&viewport, &oldViewports);

}

void ShadowMap::SendShadowParam()
{
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
	//リソース更新
	dc->UpdateSubresource(m_shadowCb.GetBody(), 0, NULL, &m_shadowCbEntity, 0, 0);
	//定数バッファの設定
	dc->PSSetConstantBuffers(enSkinModelCBReg_Shadow, 1, &m_shadowCb.GetBody());

	//リソースのセット
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		dc->PSSetShaderResources(enSkinModelCBReg_Shadow1 + i, 1, &m_KshadowMapRT[i].GetRenderTargetSRV());
	}
}

void ShadowMap::RenderToShadowMap()
{

	//デバコン取得
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		//ビューの取得
		ID3D11RenderTargetView* rtv[]{
			m_KshadowMapRT[i].GetRenderTargetView()
		};
		ID3D11DepthStencilView* dsv[]{
			m_KshadowMapRT[i].GetDepthStensilView()
		};
		//ビューポートも取得
		D3D11_VIEWPORT* vp[]{
			m_KshadowMapRT[i].GetViewport()
		};
		//ビューをセット
		dc->OMSetRenderTargets(1, rtv, *dsv);
		//ビューポートもセット
		dc->RSSetViewports(1, *vp);

		//レンダーターゲットを白で塗りつぶす。
		float ClearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_KshadowMapRT[i].ClearRenderTarget(ClearColor);

		//シャドウキャスターとして登録されてるやつ分描画
		for (auto& caster : m_shadowCasters) {
			//もうカメラ座標軸に変換済みなのでプロジェクション行列はいらない？
			caster->Draw(m_lightViewMatrix[i], m_lightProjMatirx[i], enRenderMode_CreateShadowMap);
		}
	}
	//キャスターを削除
	m_shadowCasters.clear();
}

void ShadowMap::EndRender()
{
	//デバイスコンテキストの取得
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	//もとに戻す
	dc->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);

	//ビューポートももとに戻す
	dc->RSSetViewports(viewport, &oldViewports);

	//解放
	oldDepthStencilView->Release();
	oldRenderTargetView->Release();
}

