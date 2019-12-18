#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。
};

