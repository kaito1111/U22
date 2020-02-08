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
	//�T���v�� �G�t�F�N�g�ȊO�͏����DeleteGO����Ȃ��̂ŋC��t���āI
	if (GetAsyncKeyState('H')) {
		//2D�̃T���v��
		//ex2D* ex2d = NewGO<ex2D>(1, "ex2D");
		//�G�t�F�N�g�̃T���v��
		exEffect* exEf = NewGO<exEffect>(1, "exEf");
	}
}  