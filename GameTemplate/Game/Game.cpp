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
}

Game::~Game()
{
}

bool Game::Start()
{
	//Stage* stage = NewGO<Stage>(0, "stage");
	NewGO< KaitoTask>(2, "kaito");
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
		ex2D* ex2d = NewGO<ex2D>(4, "ex2D");
		
		//デバッグ用UnitychanのNewGO
		NewGO<DebugMan>(0, "debugman");

		//エフェクトの作成
		if (!effect->IsPlay()) {
			effect = NewGO<Effect>(1);
			effect->Play(L"Assets/effect/test.efk");
			effect->SetPosition({ 0,0, 0 });
			effect->SetScale(CVector3::One() * 20);
		}
		//サウンドの再生
		m_se.Play(false);
	}
}