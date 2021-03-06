#pragma once
#include"level/Level.h"
#include<stdio.h>
class stageObjectStopFloor;
class Goal;
class RorlingRock;
class Iwa;
class stageObject1;
class moveFloor;
class MoveFloor2;
class GameObjectScythe;
class StageObjectDossun;
class StageObjectMagma;
class Gimmick_Button;
class CheckPointgenerator;
class stageObjectJenerator : public IGameObject
{
public:
	stageObjectJenerator();
	~stageObjectJenerator();
	void setStageNum(const int& num) {
		StageNum = num;
	}
	/*void setStage(enum Stage stageee) {
		
	}*/

private:
	int StageNum = 2;
	//enum stageNum{ stage1, stage2, stage3};
	//オブジェクト
	
	stageObjectStopFloor* stopFloor = nullptr;
	Goal* goal = nullptr;
	StageObjectMagma* magma = nullptr;
	moveFloor* movefloor = nullptr;
	stageObject1* object1 = nullptr;
	RorlingRock* rorlingRock = nullptr;
	Iwa* iwa = nullptr;
	GameObjectScythe* scythe = nullptr;
	StageObjectDossun* dossun = nullptr;

	void Update();
	bool Start();
	void OnDestroy()override;
	//今回はレベル君を使うぜ！
	Level level;
	Gimmick_Button* moveButtonPtr = nullptr;
	moveFloor* moveFloorPtr = nullptr;
	MoveFloor2* moveFloor2Ptr = nullptr; 
	float Floor2PosX = 0.0f;

	//リスト
	std::list<IGameObject*> GameObjList;

	std::list< stageObjectStopFloor*> stopFloorList;
	std::list<Goal*> goalList;
	std::list<Iwa*> IwaList;
	std::list<moveFloor*> moveFloorList;
	std::list<GameObjectScythe*> GameObjectScytheList;
	std::list<StageObjectDossun*> StageObjectDossunList;
	std::list<StageObjectMagma*> StageObjectMagmaList;

	CheckPointgenerator* m_PointGenerator = nullptr;
};

