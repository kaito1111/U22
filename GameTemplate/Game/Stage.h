#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
#include"physics/PhysicsStaticObject.h"
#include"PlayerData.h"
class stageObjectJenerator;
class Game;
class Goal;
class Stage : public PlayerData
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Draw();
	void setStageNum(const int& num) {
		SaveStageData();
		nowStage = num;
	}
	const int& GetNowStage() const
	{
		return nowStage;
	}
private:
	int nowStage = 0;
	int count = 0;
	bool newStage = false;
                   //ゲームクラス
	Goal* goal = nullptr;
	stageObjectJenerator* generator = nullptr;//ｼﾞｪﾈﾚｰﾀｰ
	SkinModel m_model;						  //スキンモデル。
	CVector3 m_position;
	
	PhysicsStaticObject m_phyStaticObuject;   //静的物理オブジェクト
	 
};
