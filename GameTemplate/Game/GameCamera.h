#pragma once
#include "Player.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

private:
	bool Start()override;
	void Update()override;
	Player* m_Player = nullptr;
};