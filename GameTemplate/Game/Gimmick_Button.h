#pragma once

#include "Player.h"

class Gimmick_Button : public IGameObject
{
public:
	Gimmick_Button();
	~Gimmick_Button();

	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
private:
	bool Start();
	void Update();

	SkinModelRender* m_Skin = nullptr;

	AnimationClip m_animeData[1] = { };
	CVector3 m_Position = { 300.0f,0.0f,0.0 };

	SkinModelRender* m_PushSkin = nullptr;

	Player* m_Player[2] = {};

	bool IsOn = false;
};