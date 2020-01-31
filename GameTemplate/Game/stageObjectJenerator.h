#pragma once
#include"level/Level.h"
#include<stdio.h>
class Iwa;
class stageObjectJenerator : public IGameObject
{
public:
	stageObjectJenerator();
	~stageObjectJenerator();

private:
	void Update();
	Level level;
	//using IwaPtr = std::unique_ptr<Iwa>;

	std::list<Iwa*> IwaList;

	Iwa* iwa = nullptr;

};

