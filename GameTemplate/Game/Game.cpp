#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"
#include "Sample/DebugMan.h"
#include "StageSelect/TitleStage.h"
#include "stageObject/Goal.h"
#include "level/Level.h"
#include "StageSelect/StageSelect.h"
#include "CheckPointgenerator.h"
#include "Network/NetworkLogic.h"

StageSelect;
Game::Game()
{
}

Game::~Game()
{
	//delete m_task;
	DeleteGO(m_task);
	DeleteGO(stage);
}

bool Game::Start()
{
	//1î‘ñ⁄
	m_task = NewGO<KaitoTask>(0);

	//2î‘ñ⁄
	//StageSelect* stage = NewGO<StageSelect>(0, "stageselect");
	stage = NewGO<Stage>(0, "stage");
	return true;
}

void Game::Update()
{
}

void Game::Draw()
{
	//~Drawèàóù
}
