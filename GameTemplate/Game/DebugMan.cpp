#include "stdafx.h"
#include "DebugMan.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//ゴールの位置
		//m_pos = { -358.0f,925.0f,0.0f };
		m_pos = CVector3::Zero();
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
	
		//シャドウ関連の初期化処理
		{
			//グラフィックスエンジンからシャドウマップを取得
			m_shadowMap = g_graphicsEngine->GetShadowMap();
			//影を落とすカメラの座標
			m_lightCameraPosition = { 0.0f, 4000.0f, 0.0f };
			//影を落とす注視点の座標
			m_lightCameraTarget = CVector3::Zero();;/*CVector3::Zero();*/
		}
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//シャドウ関連の更新処理
		{
			//シャドウキャスター登録
			m_shadowMap->RegistShdowCaster(&m_skinModel);
			//ライトの座標を更新
			m_shadowMap->UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
		}

		if (GetAsyncKeyState('A')) {
			m_pos.x += 5;
		}
		else if(GetAsyncKeyState('D')){
			m_pos.x -= 5;
		}

		//ワールド行列更新
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::PreRender()
	{
		//シャドウマップにレンダリング
		{
			//描画設定のバックアップ
			m_shadowMap->BiginRender();
			//シャドウマップ用の描画設定に切り替えて
			//登録されているシャドウキャスターの影を描画
			m_shadowMap->RenderToShadowMap();
			//描画設定をもとに戻す
			m_shadowMap->EndRender();
		}
	}



	void DebugMan::Draw()
	{
		//通常レンダリング
		{
			m_skinModel.Draw(
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix(),
				0,
				g_graphicsEngine->GetShadowMap()->GetLightViewMatirx(),
				g_graphicsEngine->GetShadowMap()->GetLightProjMatirx()
			);
		}
	}
}