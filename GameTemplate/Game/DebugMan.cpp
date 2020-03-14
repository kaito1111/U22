#include "stdafx.h"
#include "DebugMan.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//シャドウキャスター登録
		g_graphicsEngine->GetShadowMap()->RegistShdowCaster(&m_skinModel);
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
			//この関数が中でView切り替えてるからバックアップ必要
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