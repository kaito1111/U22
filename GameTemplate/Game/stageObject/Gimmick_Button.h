#pragma once

#include "Player.h"
#include "physics/PhysicsStaticObject.h"

class Gimmick_Button : public IGameObject
{
public:
	Gimmick_Button();
	~Gimmick_Button();

	void SetPosition(const CVector3 pos) {
		m_Position = pos;
	}
	bool GetOn() {
		return IsOn;
	}
private:
	bool Start();
	void Update();

	SkinModelRender* m_Skin = nullptr;
	AnimationClip m_animeData[1] = { };
	CVector3 m_Position = { 300.0f,0.0f,0.0 };
	SkinModelRender* m_PushSkin = nullptr;
	PhysicsStaticObject m_physicsOcject;

	SoundSource m_Se;
	Player* m_Player[2] = {};

	bool IsOn = false;
};