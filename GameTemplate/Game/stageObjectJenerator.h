#pragma once
#include"level/Level.h"
#include<stdio.h>
class Goal;
class RorlingRock;
class Iwa;
class stageObject1;
class moveFloor;
class GameObjectScythe;
class StageObjectDossun;
class StageObjectMagma;
class stageObjectJenerator : public IGameObject
{
public:
	stageObjectJenerator();
	~stageObjectJenerator();

private:
	//�I�u�W�F�N�g
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

	//����̓��x���N���g�����I
	Level level;
	std::list<Goal*> goalList;
	std::list<Iwa*> IwaList;
	std::list<moveFloor*> moveFloorList;
	std::list<GameObjectScythe*> GameObjectScytheList;
	std::list<StageObjectDossun*> StageObjectDossunList;
	std::list<StageObjectMagma*> StageObjectMagmaList;
};

