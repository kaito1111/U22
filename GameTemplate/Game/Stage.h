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
private:
	int nowStage = 2;
	int count = 0;
	bool newStage = false;
                   //ゲームクラス
	Goal* goal = nullptr;
	stageObjectJenerator* generator = nullptr;//ｼﾞｪﾈﾚｰﾀｰ
	SkinModel m_model;						  //スキンモデル。
	CVector3 m_position;
	
	PhysicsStaticObject m_phyStaticObuject;   //静的物理オブジェクト
	 
};
