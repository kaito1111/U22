#include "stdafx.h"
#include "stageObject/Goal.h"
#include "GemeLoop.h"
#include "Game.h"
#include "StageSelect/StageSelect.h"
GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{

}

bool GameLoop::Start()
{
	m_game = FindGO<Game>("game");
	m_fade = NewGO<Fade>(0, "fade");
	return true;
}

void GameLoop::Update()
{
	if (m_fade->GetLengh() < 220.0f
		&&!m_DeleteGame) {
		DeleteGO(m_game);
		m_DeleteGame = true;
	}
	if (m_fade->GetLengh() < 210.0f) {
		DeleteGO(this);
		StageSelect* stageselect = NewGO<StageSelect>(0, "stageselect");
		//select = NewGO<StageSelect>(0, "stageselect");
	}
}
