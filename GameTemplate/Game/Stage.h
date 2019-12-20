#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。

};
