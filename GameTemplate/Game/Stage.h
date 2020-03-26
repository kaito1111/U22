#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
#include"physics/PhysicsStaticObject.h"
class stageObjectJenerator;
class Game;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:
                   //�Q�[���N���X
	stageObjectJenerator* generator = nullptr;//�ު�ڰ��
	SkinModel m_model;						  //�X�L�����f���B
	CVector3 m_position;
	
	PhysicsStaticObject m_phyStaticObuject;   //�ÓI�����I�u�W�F�N�g
	 
};
