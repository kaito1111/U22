#include "stdafx.h"
#include "stageObject/Goal.h"
#include "GemeLoop.h"
#include "Stage.h"

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
	}
	if (m_fade->GetLengh() < 200.0f) {
		Stage* stage = NewGO<Stage>(0, "stage");
		stage->setStageNum(2);
	}
}
