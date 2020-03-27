#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"
#include "DebugMan.h"
#include "GameCamera.h"

Game::Game()
{
	//サウンドの初期化
	m_se.Init(L"Assets/sound/coinGet.wav");

	//メインレンダーターゲットにかかれた絵を
	//フレームバッファにコピーするためにスプライトを初期化
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

}

Game::~Game()
{
	//解放
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
}

bool Game::Start()
{
	//1番目
	NewGO< KaitoTask>(5, "kaito");
	//2番目
	Stage* stage = NewGO<Stage>(0, "stage");
	//NewGO<DirectionLight>(3, "light");
	effect = NewGO<Effect>(1);

	return true;
}

void Game::Update()
{
	Sample();
}

//いろいろなサンプル
void Game::Sample()
{
	if (GetAsyncKeyState('H'))
	{
		//2Dのサンプル
		//ex2D* ex2d = NewGO<ex2D>(4, "ex2D");
		
		//デバッグ用UnitychanのNewGO
		NewGO<DebugMan>(0, "debugman");

		//エフェクトの作成
		if (!effect->IsPlay()) {
			effect = NewGO<Effect>(1);
			effect->Play(L"Assets/effect/test.efk");
			effect->SetPosition({ 100,0, 0 });
			effect->SetScale(CVector3::One() * 20);
		}
		//サウンドの再生
		m_se.Play(false);
	}
}

void Game::Draw()
{
	//~Draw処理
}

void Game::PostRender()
{
	//ドロー
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}