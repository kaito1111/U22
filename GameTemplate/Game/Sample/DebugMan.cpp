#include "stdafx.h"
#include "DebugMan.h"
#include "SampleScene.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//ゴールの位置
		//m_pos = { -358.0f,925.0f,0.0f };
		m_pos = { 0.0f, 21.0f, 0.0f };
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
		m_charaCon.Init(20.0f, 25.0f, m_pos);
	
		//シャドウ関連の初期化処理
		{
			//グラフィックスエンジンからシャドウマップを取得
			m_shadowMap = g_graphicsEngine->GetShadowMap();
			//影を落とすカメラの座標
			//m_lightCameraPosition = { 0.0f, 4000.0f, 0.0f };
			//影を落とす注視点の座標
			m_lightCameraTarget = CVector3::Zero();;/*CVector3::Zero();*/
		}
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		if (GetAsyncKeyState('A')) {
			m_moveSpeed.x = 5.0f;
		}
		else if(GetAsyncKeyState('D')){
			m_moveSpeed.x = -5.0f;
		}
		else {
			m_moveSpeed.x = 0;
		}
		if (GetAsyncKeyState('S')) {
			m_moveSpeed.z = 5.0f;
		}
		else if (GetAsyncKeyState('W')) {
			m_moveSpeed.z = -5.0f;
		}
		else {
			m_moveSpeed.z = 0;
		}

		m_moveSpeed.y = GRAVITY;

		//移動量計算
		m_pos = m_charaCon.Execute(1.0f, m_moveSpeed);

		//ワールド行列更新
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::PreRender()
	{
		//シャドウマップにレンダリング
		{
			//描画設定のバックアップ
			//m_shadowMap->BiginRender();
			//シャドウキャスター登録
			m_shadowMap->RegistShdowCaster(&m_skinModel);
			//シャドウマップ用の描画設定に切り替えて
			//登録されているシャドウキャスターの影を描画
			//m_shadowMap->RenderToShadowMap();
			//描画設定をもとに戻す
			//m_shadowMap->EndRender();
		}
	}



	void DebugMan::Draw()
	{
		//通常レンダリング
		{
			m_skinModel.Draw(
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix(),
				0
			);
		}
	}
}