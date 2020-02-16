#include "stdafx.h"
#include "Game.h"
#include"Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"

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
	//NewGO< KaitoTask>(3, "kaito");
	//Stage* stage = NewGO<Stage>(2, "stage");

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
		Effect* effect = NewGO<Effect>(1);
		effect->Play(L"Assets/effect/test.efk");
		effect->SetPosition({ 0,0, 0 });
		effect->SetScale(CVector3::One() * 20);

		//サウンドの再生
		m_se.Play(false);
	}
}