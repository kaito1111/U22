#pragma once
class StageSelect;
class PlayerData;
class Player;
class NewOrContinue : public IGameObject
{
public:
	NewOrContinue();
	~NewOrContinue();
private:
	bool Start();
	void Update();
	StageSelect* stageSelect = nullptr;
	Player* player[2] = {};
	PlayerData* playerData = nullptr;
	SpriteRender* m_spriteRender = nullptr;

};

