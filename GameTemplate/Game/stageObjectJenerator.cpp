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
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				auto GoalPtr = new Goal(
					L"Assets/modelData/Goal.cmo",
					objData.position,
					objData.rotation);
				goalList.push_back(GoalPtr);
				return true;
			}
			return false;
		});
	}	

	//ステージ二つ目。未完成。ふｃきｎ。
	if (StageNum == 1) {
		//ドッスン
		level.Init(L"Assets/level/stageDossun.tkl", [&](const auto& objData)
		{
			if (wcscmp(objData.name, L"Dossun") == 0) {
				auto StageObjectDossunPtr = new StageObjectDossun(
					L"Assets/modelData/Dossun.cmo",
					objData.position,
					objData.rotation);
				StageObjectDossunList.push_back(StageObjectDossunPtr);
				return true;
			}
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				auto GoalPtr = new Goal(
					L"Assets/modelData/Goal.cmo",
					objData.position,
					objData.rotation);
				goalList.push_back(GoalPtr);
				return true;
			}
		});
	}

	//各オブジェクトのスタートが走ります
	for (auto& i : IwaList) {
		i->Start();;
	}
	for (auto& i : moveFloorList) {
		i->Start();
	}
	for (auto& i : GameObjectScytheList) {
		i->Start();
	}
	for (auto& i : StageObjectDossunList) {
		i->Start();
	}
	for (auto& i : StageObjectMagmaList) {
		i->Start();;
	}
	for (auto& i : goalList) {
		i->Start();
	}
	return true;
}



void stageObjectJenerator::Update()
{
	level.Draw();
	for (auto& i : IwaList) {
		i->Update();
	}
	for (auto& i : moveFloorList) {
		i->Update();
	}
	for (auto& i : GameObjectScytheList) {
		i->Update();
	}
	for (auto& i : StageObjectDossunList) {
		i->Update();
	}
	for (auto& i : StageObjectMagmaList) {
		i->Update();
	}
	for (auto& i : goalList) {
		i->Update();
	}
}

void stageObjectJenerator::Draw()
{
	for (auto& i : IwaList) {
		i->Draw();
	}
	for (auto& i : moveFloorList) {
		i->Draw();
	}
	for (auto& i : GameObjectScytheList) {
		i->Draw();
	}
	for (auto& i : StageObjectDossunList) {
		i->Draw();
	}
	for (auto& i : StageObjectMagmaList) {
		i->Draw();
	}
	for (auto& i : goalList) {
		i->Draw();
	}
}