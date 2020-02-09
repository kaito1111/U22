#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"Stage.h"
#include"stageObject1.h"
#include "GameCamera.h"
#include "graphics/Shader.h"
#include "graphics/2D/ex2D.h"
#include "exEffect.h"
#include"stageObjectJenerator.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	NewGO<GameCamera>(1, "camera");
	Stage* stage = NewGO<Stage>(1, "stage");
	//2Dのサンプル
	ex2D* ex2d = NewGO<ex2D>(1, "ex2D");

	const int PlayerNum = 2;
	for (int i = 0; i < PlayerNum; i++)
	{
		Player* player = NewGO<Player>(1, "player");
		CVector3 position = CVector3::Zero();
		position.x = 100.0*i;
		player->SetPosition(position);
		player->SetPadNo(i);
	}

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