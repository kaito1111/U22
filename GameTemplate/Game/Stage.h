#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
#include"physics/PhysicsStaticObject.h"
class stageObjectJenerator;
class Game;
class Goal;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Draw();
	void setStageNum(const int& num) {
		nowStage = num;
	}
	const int& GetNowStage() const
	{
		return nowStage;
	}
private:
	void OnDestroy()override;
	int nowStage = 0;
	int count = 0;
	bool newStage = false;
                   //�Q�[���N���X
	Goal* goal = nullptr;
	stageObjectJenerator* generator = nullptr;//�ު�ڰ��
	SkinModel m_model;						  //�X�L�����f���B
	CVector3 m_position;
	
	PhysicsStaticObject m_phyStaticObuject;   //�ÓI�����I�u�W�F�N�g
	 
};
