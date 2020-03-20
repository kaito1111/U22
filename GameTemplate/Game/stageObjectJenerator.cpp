#include "stdafx.h"
#include "stageObjectJenerator.h"
#include "Iwa.h"
#include"stageObject1.h"
#include"moveFloor.h"
#include"RorlingRock.h"
#include"GameObjectScythe.h"
#include"StageObjectDossun.h"
#include"StageObjectMagma.h"
#include"Goal.h"
stageObjectJenerator::stageObjectJenerator()
{
}


stageObjectJenerator::~stageObjectJenerator()
{
	for (auto i : IwaList) {
		delete i;
	}
	for (auto i : moveFloorList) {
		delete i;
	}
	for (auto i : GameObjectScytheList) {
		delete i;
	}
	for (auto i : StageObjectDossunList) {
		delete i;
	}
	for (auto i : StageObjectMagmaList) {
		delete i;
	}
	for (auto i : goalList) {
		delete i;
	}
}

bool stageObjectJenerator::Start()
{
	if (StageNum == 0) {
		level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
		{
			//動く床
			if (wcscmp(objData.name, L"moveFloor") == 0) {
				auto moveFloorPtr = new moveFloor(
					L"Assets/modelData/moveFloor.cmo",
					objData.position,
					objData.rotation);
				moveFloorList.push_back(moveFloorPtr);
				return true;
			}

			return false;
		});
	}	
	//ステージ二つ目。未完成。ふｃきｎ。
	if (StageNum == 1) {
	}

	return true;
}

void stageObjectJenerator::Update()
{
	level.Draw();
	for (auto& i : IwaList) {
		i->Start();
		i->Update();
		i->Draw();
	}
	for (auto& i : moveFloorList) {
		i->Start();
		i->Update();
		i->Draw();
	}
	for (auto& i : GameObjectScytheList) {
		i->Start();
		i->Update();
		i->Draw();
	}
	for (auto& i : StageObjectDossunList) {
		i->Start();
		i->Update();
		i->Draw();
	}
	for (auto& i : StageObjectMagmaList) {
		i->Start();
		i->Update();
		i->Draw();
	}
	for (auto& i : goalList) {
		i->Start();
		i->Update();
		i->Draw();
	}
}

        