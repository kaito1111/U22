#pragma once
#include "Game.h"
#include "GameCamera.h"
#include "Fade.h"
class StageSelect;
class GameLoop :public IGameObject
{
public:
	GameLoop();
	~GameLoop();

private:
	bool Start();
	void Update();
	Game* m_game = nullptr;
	//GameCamera* m_camera = nullptr;
	Fade* m_fade = nullptr;
	//StageSelect* select = nullptr;
	bool m_DeleteGame = false;
};