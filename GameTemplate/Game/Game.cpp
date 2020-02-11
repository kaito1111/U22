#include "stdafx.h"
#include "Game.h"
#include"Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	NewGO< KaitoTask>(3, "kaito");
	Stage* stage = NewGO<Stage>(2, "stage");

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

		//エフェクトの作成
		Effect* effect = NewGO<Effect>(0);
		effect->Play(L"Assets/effect/test.efk");
		effect->SetScale(CVector3::One() * 10);

		//サウンドの初期化
		m_se.Init(L"Assets/sound/coinGet.wav");
		//サウンドの再生
		m_se.Play(false);
	}
}