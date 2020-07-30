#include "stdafx.h"
#include "stageObject/Goal.h"
#include "GemeLoop.h"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

bool GameLoop::Start()
{
	m_game = FindGO<Game>("game");
	m_camera = FindGO<GameCamera>("camera");
	m_fade = NewGO<Fade>(0, "fade");
	m_goal = FindGO<Goal>(0, "goal");
	return true;
}

void GameLoop::Update()
{
}
