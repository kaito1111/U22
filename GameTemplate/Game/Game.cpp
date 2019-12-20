#include "stdafx.h"

#include "Game.h"
#include "Player.h"
#include"Stage.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	Player* player = NewGO<Player>(1, "player");
	Stage* stage = NewGO<Stage>(1, "stage");
	return true;
}

void Game::Update()
{

}