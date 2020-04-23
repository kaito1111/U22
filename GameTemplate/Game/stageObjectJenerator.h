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
class stageObjectJenerator : public IGameObject
{
public:
	stageObjectJenerator();
	~stageObjectJenerator();
	void setStageNum(const int& num) {
		stageNum = num;
	}
	/*void setStage(enum Stage stageee) {
		
	}*/

private:
	int stageNum = 1;
	//enum stageNum{ stage1, stage2, stage3};
	//オブジェクト
	
	/*stageObjectStopFloor* stopFloor = nullptr;
	Goal* goal = nullptr;
	StageObjectMagma* magma = nullptr;
	moveFloor* movefloor = nullptr;
	stageObject1* object1 = nullptr;
	RorlingRock* rorlingRock = nullptr;
	Iwa* iwa = nullptr;
	GameObjectScythe* scythe = nullptr;
	StageObjectDossun* dossun = nullptr;*/

	void Update();
	bool Start();
	void Draw();
	//今回はレベル君を使うぜ！
	Level level;
	Gimmick_Button* moveButtonPtr = nullptr;
	moveFloor* moveFloorPtr = nullptr;
	MoveFloor2* moveFloor2Ptr = nullptr;
	/*std::list< stageObjectStopFloor*> stopFloorList;
	std::list<Goal*> goalList;
	std::list<Iwa*> IwaList;
	std::list<moveFloor*> moveFloorList;
	std::list<GameObjectScythe*> GameObjectScytheList;
	std::list<StageObjectDossun*> StageObjectDossunList;
	std::list<StageObjectMagma*> StageObjectMagmaList;*/
};

