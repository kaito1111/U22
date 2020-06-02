#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	//シャドウマップ生成用のレンダリングターゲットを作成
	//解像度は2048*2048
	//テクスチャのフォーマットはR成分のみ32bit浮動小数点型。
	m_shadowMapRT.Create(
		2048,
		2048,
		DXGI_FORMAT_R32_FLOAT
	);

	m_lightCameraPosition = { -358.0f, 2000.0, 0.0f };
	m_lightCameraTarget = CVector3::Zero();
}

ShadowMap::~ShadowMap()
{
}

//void ShadowMap::Update()
//{
//	//UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
//}

void ShadowMap::UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir)
{
	//ライトの方向によって、ライトの上方向を決める。
	CVector3 lightCameraUpAxis;
	//fabsf()はたしか絶対値
	if (fabsf(lightDir.y) > 0.99998f) {
		//ほぼ真上or真下を向いているので、{ 1,0,0 }を上方向にする。
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		//真上or真下向いていないので、{ 0,1,0 }を上方向にする。
		lightCameraUpAxis = CVector3::AxisY();
	}
	//カメラの上方向が決定したので、ライトビュー行列を計算
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);

	//ライトプロジェクション行列を作成する。
	//太陽光からの影を落としたいなら、平行投影行列を作成する。
	//ここのw,hをいじるとシャドウマップの範囲が変わる！
	m_lightProjMatirx.MakeOrthoProjectionMatrix(
		5000,
		5000,
		0.1f,
		5000.0f
	);
}

void ShadowMap::UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	//ライトの方向を計算
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//視点と注視点近すぎ
		//恐らくバグなのでクラッシュ
		std::abort();
	}
	//正規化
	lightDir.Normalize();
	//影をおとす処理
	UpdateFromLightDirection(m_lightCameraPosition, lightDir);
}

void ShadowMap::UpdateFromLightTarget()
{
	//ライトの方向を計算
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//視点と注視点近すぎ
		//恐らくバグなのでクラッシュ
		std::abort();
	}
	//正規化
	lightDir.Normalize();
	//影をおとす処理
	UpdateFromLightDirection(m_lightCameraPosition, lightDir);
}

void ShadowMap::BiginRender()
{
	//デバコン取得
	auto dc = g_graphicsEngine->GetD3DDeviceContext();
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

void ShadowMap::RenderToShadowMap()
{
	auto dc = g_graphicsEngine->GetD3DDeviceContext();
	//レンダリングターゲットを切り替え。
	ID3D11RenderTargetView* rts[] = {
		//シャドウマップ用のレンダリングターゲット
		m_shadowMapRT.GetRenderTargetView()
	};
	//深度ステンシルビューの設定
	dc->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//ビューポートの設定
	dc->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//シャドウマップをクリア
	//１番奥のZは1.0なので、1.0で塗りつぶす
	float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//シャドウキャスターをシャドウマップにレンダリング
	for (auto& caster : m_shadowCasters) {
		//登録されているシャドウキャスターの数だけ回す
		//シャドウマップ描画
		caster->Draw(
			m_lightViewMatrix,
			m_lightProjMatirx,
			enRenderMode_CreateShadowMap
		);
	}
	//キャスターをクリア
	m_shadowCasters.clear();
}

void ShadowMap::EndRender()
{
	//デバイスコンテキストの取得
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

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

