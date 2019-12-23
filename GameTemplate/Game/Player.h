#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	CVector3 GetPosition() { 
		return m_position; 
	}
	CVector3 GetForward() {
		return m_forward;
	}
private:
	~Player();
	void Update();
	void Draw();
	SkinModel m_model;									//スキンモデル。
	CharacterController m_characon;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_forward = CVector3::Front();
};

