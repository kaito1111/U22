#pragma once
class StageSelect;
class Player;
class Game;
#include "PlayerData.h"
class NewOrContinue : public PlayerData
{
public:
	NewOrContinue();
	~NewOrContinue();
private:
	bool Continue = false;
	bool padB = false;
	bool Start();
	void Update();
	Game* game = nullptr;
	StageSelect* stageSelect = nullptr;
	SpriteRender* m_spriteRender = nullptr;
	
};

