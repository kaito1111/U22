#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	CVector3 GetPosition() { 
		return m_Position; 
	}
private:
	void Update();
	void Draw();
	SkinModel m_model;									//スキンモデル。
	CharacterController m_CharaCon;
	CVector3 m_Position = CVector3::Zero();
};

