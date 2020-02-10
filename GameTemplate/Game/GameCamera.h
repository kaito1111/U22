#pragma once
#include "Player.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

private:
	int m_PlayerNum = 0;
	bool Start()override;
	void Update()override;
	Player* m_Player[2] = {};
	float Decline = 0.0f;		//‰º‚ÌŒÀŠE
};