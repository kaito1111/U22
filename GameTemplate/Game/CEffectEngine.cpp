#include "stdafx.h"
#include "CEffectEngine.h"

namespace myEngine {

	CEffectEngine::CEffectEngine()
	{
	}

	CEffectEngine::~CEffectEngine()
	{
		//解放
		Release();
	}

	void CEffectEngine::Release()
	{
		if (m_effekseerRenderer == nullptr) {
			//インスタンス破棄
			m_effekseerRenderer->Destroy();
		}
		if (m_manager == nullptr) {
			//インスタンス破棄
			m_manager->Destroy();
		}
	}

	void CEffectEngine::Init()
	{
		//レンダラーを初期化。
		m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
			g_graphicsEngine->GetD3DDevice(),					//D3Dデバイス。
			g_graphicsEngine->GetD3DDeviceContext(),			//D3Dデバイスコンテキスト。	
			2000												//板ポリの最大数。
		);
		//エフェクトマネージャを初期化。
		m_manager = Effekseer::Manager::Create(10000);

		// 描画用インスタンスから描画機能を設定
		m_manager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

		// 描画用インスタンスからテクスチャの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		m_manager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
	}

	void CEffectEngine::Update()
	{
		//エフェクサーのカメラ設定
		m_effekseerRenderer->SetCameraMatrix(g_camera3D.GetViewMatrix());
		m_effekseerRenderer->SetProjectionMatrix(g_camera3D.GetViewMatrix());
		//更新
		m_manager->Update();
	}

	void CEffectEngine::Render()
	{
		//g_cameraからカメラ行列とプロジェクション行列をコピー
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);

		//カメラ行列とプロジェクション行列を原点に設定。
		//tkEngine側はカメラの中央に出るようになってた希ガス
		EffectEngineObj().GetEffekseerRenderer()->SetCameraMatrix(efCameraMat);
		EffectEngineObj().GetEffekseerRenderer()->SetProjectionMatrix(efProjMat);

		//Effekseerを更新。
		EffectEngineObj().GetEffekseerManager()->Update();

		//エフェクト描画用のレンダリング設定。
		m_effekseerRenderer->BeginRendering();
		//エフェクトの描画処理
		m_manager->Draw();
		//レンダリング設定をもとに戻す。
		m_effekseerRenderer->EndRendering();
	}

	Effekseer::Effect* CEffectEngine::CreateEffect(const wchar_t* filepath)
	{
		//作成
		return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filepath);
	}

	Effekseer::Handle CEffectEngine::Play(Effekseer::Effect* effect)
	{
		//EffectのUpdateでワールド座標は計算
		return m_manager->Play(effect, 0, 0, 0);
	}
}