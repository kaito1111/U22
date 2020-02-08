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
	NewGO< GameCamera>(1, "camera");
	Player* player = NewGO<Player>(1, "player");
	Stage* stage = NewGO<Stage>(1, "stage");

	return true;
}

void Game::Update()
{
	//サンプル エフェクト以外は勝手にDeleteGOされないので気を付けて！
	if (GetAsyncKeyState('H')) {
		//2Dのサンプル
		//ex2D* ex2d = NewGO<ex2D>(1, "ex2D");
		//エフェクトのサンプル
		exEffect* exEf = NewGO<exEffect>(1, "exEf");
	}
}  