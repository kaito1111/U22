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
#include "Player.h"
Game::Game()
{
	//サウンドの初期化
	m_se.Init(L"Assets/sound/coinGet.wav");

	//メインレンダーターゲットにかかれた絵を
	//フレームバッファにコピーするためにスプライトを初期化
	m_copyMainRtToFrameBufferSprite.Init(
		Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

}

Game::~Game()
{
	DeleteGO(m_task);//1回
}

bool Game::Start()
{
	//1番目
	m_task = NewGO<KaitoTask>(2,"kaitoTask");

	//2番目
	//StageSelect* stage = NewGO<StageSelect>(0, "stageselect");
	m_Stage = NewGO<Stage>(0, "stage");
	m_Stage->setStageNum(StageNum);
	//NewGO<DirectionLight>(3, "light");
	effect = NewGO<Effect>(1);		
	//CheckPointgenerator* PointGenerator = NewGO< CheckPointgenerator>(0, "checkpointgenerator");
	//PointGenerator->Load(L"Assets/level/Corse_Level_1.tkl");
	//if (Continue) {
	//	GamePlayer* pl1 = FindGO<GamePlayer>("player1");
	//	GamePlayer* pl2 = FindGO<GamePlayer>("player2");
	//	pl1->SetPosition(player1Pos);
	//	pl2->SetPosition(player2Pos);
	//}
	return true;
}

void Game::Update()
{
	//if (g_Pad[0].IsTrigger(enButtonDown)) {
	//	
	//	DeleteGO(this);
	//}
	Sample();
	m_postEffect.Update();
}

void Game::OnDestroy()
{
	DeleteGO(m_Stage);
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

	auto a = Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV();

	//ドロー
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}