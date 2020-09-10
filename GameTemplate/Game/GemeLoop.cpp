#include "stdafx.h"
#include "stageObject/Goal.h"
#include "GemeLoop.h"
#include "Game.h"
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
	return true;
}

void GameLoop::Update()
{
	if (m_fade->GetLengh() < 210.0f) {
		DeleteGO(m_game);
		DeleteGO(this);
		Game* game = NewGO<Game>(0, "game");
		game->SetStage(2);
		//select = NewGO<StageSelect>(0, "stageselect");
	}
}
