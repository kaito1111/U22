#pragma once
class StageSelect;
class Player;
#include "PlayerData.h"
class NewOrContinue : public PlayerData
{
public:
	NewOrContinue();
	~NewOrContinue();
private:
	bool padB = false;
	bool Start();
	void Update();
	StageSelect* stageSelect = nullptr;
	Player* player[2] = {};
	SpriteRender* m_spriteRender = nullptr;

};

