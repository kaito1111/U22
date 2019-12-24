#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"

class stageObject1 : public IGameObject
{
	//ドッスン棘やで。
public:
	stageObject1();
	~stageObject1();
	void Update();

private:
	SkinModel m_model;  //スキンモデル

	CharacterController m_characon;

	CVector3 m_position = CVector3::Zero(); //座標。

	CVector3 moveUpDown = CVector3::Zero();//上下に動かす。

	int timer = 0;     //動かした後にちょっと止める。 

	void Draw();

	void Move();//動かすぞ

	bool UpDown = false;
};

