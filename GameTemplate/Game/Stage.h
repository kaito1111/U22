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

	stageObjectJenerator* generator = nullptr;//�ު�ڰ��
	SkinModel m_model;						  //�X�L�����f���B
	
	PhysicsStaticObject m_phyStaticObuject;   //�ÓI�����I�u�W�F�N�g
	 
};
