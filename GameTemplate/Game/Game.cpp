#include "stdafx.h"

#include "Game.h"
#include "Player.h"
#include"Stage.h"
#include "GameCamera.h"

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

}