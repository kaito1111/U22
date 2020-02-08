#pragma once
#include"level/Level.h"
#include<stdio.h>

class Iwa;
class stageObject1;
class stageObject2;
class moveFloor;
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
	Iwa* iwa = nullptr;

	void Update();
	bool Start();

	//今回はレベル君を使うぜ！
	Level level;
	std::list<Iwa*> IwaList;

	

};

