#pragma once

#include "Player.h"

class Gimmick_Button : public IGameObject
{
public:
	Gimmick_Button();
	~Gimmick_Button();

private:
	bool Start();
	void Update();

	SkinModel m_Skin;
	CVector3 m_Position = { 300.0f,0.0f,0.0 };

	SkinModel m_PushSkin;

	Player* m_Player[2] = {};
};