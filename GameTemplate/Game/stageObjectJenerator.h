#pragma once
#include"level/Level.h"
#include<stdio.h>
class RorlingRock;
class Iwa;
class stageObject1;
class stageObject2;
class moveFloor;
class GameObjectScythe;
class stageObjectJenerator : public IGameObject
{
public:
	stageObjectJenerator();
	~stageObjectJenerator();

private:
	//オブジェクト
	moveFloor* movefloor = nullptr;
	stageObject1* object1 = nullptr;
	stageObject2* object2 = nullptr;
	RorlingRock* rorlingRock = nullptr;
	Iwa* iwa = nullptr;
	GameObjectScythe* scythe = nullptr;

	void Update();
	bool Start();

	//今回はレベル君を使うぜ！
	Level level;
	std::list<Iwa*> IwaList;

	

};

