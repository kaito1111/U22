#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
#include"physics/PhysicsStaticObject.h"
class stageObjectJenerator;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:

	stageObjectJenerator* generator = nullptr;//ｼﾞｪﾈﾚｰﾀｰ
	SkinModel m_model;						  //スキンモデル。
	
	PhysicsStaticObject m_phyStaticObuject;   //静的物理オブジェクト
	 
};
