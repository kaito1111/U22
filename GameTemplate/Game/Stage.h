#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
#include "physics/PhysicsStaticObject.h"
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//�X�L�����f���B
	PhysicsStaticObject PhashiphyckStaticObject;

};
