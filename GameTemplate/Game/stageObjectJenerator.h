#pragma once
#include"level/Level.h"
#include<stdio.h>
class RorlingRock;
class Iwa;
class stageObject1;
class stageObject2;
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
	StageObjectMagma* magma = nullptr;
	moveFloor* movefloor = nullptr;
	stageObject1* object1 = nullptr;
	stageObject2* object2 = nullptr;
	RorlingRock* rorlingRock = nullptr;
	Iwa* iwa = nullptr;
	GameObjectScythe* scythe = nullptr;
	StageObjectDossun* dossun = nullptr;

	void Update();
	bool Start();

	//����̓��x���N���g�����I
	Level level;
	std::list<Iwa*> IwaList;

	

};

