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
		//影を落とすカメラの座標
		m_lightCameraPosition = { 0.0f, 0.0f, -50.0f };
		//影を落とす注視点の座標
		m_lightCameraTarget = m_pos;/*CVector3::Zero();*/
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//シャドウキャスター登録
		g_graphicsEngine->GetShadowMap()->RegistShdowCaster(&m_skinModel);
		//ライトの座標を更新
		g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
		//ワールド行列更新
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::Render()
	{
		//シャドウマップにレンダリング
		{
			//デバコン取得
			auto dc = g_graphicsEngine->GetD3DDeviceContext();
			//レンダリングターゲットをバックアップ
			ID3D11RenderTargetView* oldRenderTargetView;
			ID3D11DepthStencilView* oldDepthStencilView;
			dc->OMGetRenderTargets(
				1,
				&oldRenderTargetView,
				&oldDepthStencilView
			);
			//ビューポートのバックアップ
			unsigned int viewport = 1;
			D3D11_VIEWPORT oldViewports;
			dc->RSGetViewports(&viewport, &oldViewports);

			//シャドウマップにレンダリング
			//この関数が中でTargetView切り替えてるからバックアップ必要
			g_graphicsEngine->GetShadowMap()->RenderToShadowMap();

			//もとに戻す
			dc->OMSetRenderTargets(
				1,
				&oldRenderTargetView,
				oldDepthStencilView
			);
			dc->RSSetViewports(viewport, &oldViewports);
			//解放
			oldDepthStencilView->Release();
			oldRenderTargetView->Release();
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