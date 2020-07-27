#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"
#include "Sample/DebugMan.h"
#include "StageSelect/TitleStage.h"
#include "stageObject/Goal.h"
#include "level/Level.h"
#include "StageSelect/StageSelect.h"
#include "CheckPointgenerator.h"
#include "stageObject/Iwa.h"
StageSelect;
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
		m_frameBufferDepthStencilView = nullptr;
	}
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
		m_frameBufferRenderTargetView = nullptr;
	}
	//delete m_task;
	DeleteGO(m_task);
	DeleteGO(stage);
}

bool Game::Start()
{
	//1番目
	m_task = NewGO<KaitoTask>(0);

	//2番目
	//StageSelect* stage = NewGO<StageSelect>(0, "stageselect");
	stage = NewGO<Stage>(0, "stage");
	//NewGO<DirectionLight>(3, "light");
	effect = NewGO<Effect>(1);		
	NewGO<Iwa>(0, "iwa");
	return true;
}

void Game::Update()
{
	Sample();
	m_postEffect.Update();
}

//いろいろなサンプル
void Game::Sample()
{
	if (GetAsyncKeyState('H'))
	{
		//2Dのサンプル
		//ex2D* ex2d = NewGO<ex2D>(4, "ex2D");
		
		//デバッグ用UnitychanのNewGO
		//NewGO<DebugMan>(0, "debugman");

		//エフェクトの作成
		if (!effect->IsPlay()) {
			effect = NewGO<Effect>(1);
			effect->Play(L"Assets/effect/SMode.efk");
			effect->SetPosition({ 100,0, 0 });
			effect->SetScale(CVector3::One() * 2);
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
	//ポストエフェクト描画
	//m_postEffect.Draw();

	auto a = g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV();

	//ドロー
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}