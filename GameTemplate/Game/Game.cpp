#include "stdafx.h"
#include "Game.h"
#include"Stage.h"
#include "graphics/2D/ex2D.h"
#include "exEffect.h"
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
	//2Dのサンプル
	ex2D* ex2d = NewGO<ex2D>(1, "ex2D");
	return true;
}

void Game::Update()
{
	if (GetAsyncKeyState('H'))
	{
		//エフェクトのサンプル
		exEffect* exeffect = NewGO<exEffect>(1, "exEffect");
	}
}