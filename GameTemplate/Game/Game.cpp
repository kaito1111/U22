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
	Player* Player = NewGO<Player>("player");
	return true;
}

void Game::Update()
{

}