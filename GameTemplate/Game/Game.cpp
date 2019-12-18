#include "stdafx.h"

#include "Game.h"
#include "Player.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	Player* player = NewGO<Player>(1, "player");
	return true;
}

void Game::Update()
{

}