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
	level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
	{
		////岩
		//if (wcscmp(objData.name, L"iwa") == 0) {
		//	auto IwaPtr = new Iwa(
		//		L"Assets/modelData/iwa.cmo",
		//		objData.position,
		//		objData.rotation);
		//	IwaList.push_back(IwaPtr);
		//	return true;
		//}
		////動く床
		if (wcscmp(objData.name, L"moveFloor") == 0) {
			auto moveFloorPtr = new moveFloor(
				L"Assets/modelData/moveFloor.cmo",
				objData.position,
				objData.rotation);
			moveFloorList.push_back(moveFloorPtr);
			return true;
		}
		////回る鎌
		//if (wcscmp(objData.name, L"Huriko") == 0) {
		//	auto GameObjectScythePtr = new GameObjectScythe(
		//		L"Assets/modelData/Huriko.cmo",
		//		objData.position,
		//		objData.rotation);
		//	GameObjectScytheList.push_back(GameObjectScythePtr);
		//	return true;
		//}
		////ドッスン
		//if (wcscmp(objData.name, L"Dossun") == 0) {
		//	auto StageObjectDossunPtr = new StageObjectDossun(
		//		L"Assets/modelData/Dossun.cmo",
		//		objData.position,
		//		objData.rotation);
		//	StageObjectDossunList.push_back(StageObjectDossunPtr);
		//	return true;
		//}
		////下からせりあがってくる何か
		//if (wcscmp(objData.name, L"magma") == 0) {
		//	auto StageObjectMagmaPtr = new StageObjectMagma(
		//		L"Assets/modelData/magma.cmo",
		//		objData.position,
		//		objData.rotation);
		//	StageObjectMagmaList.push_back(StageObjectMagmaPtr);
		//	return true;
		//}
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

	//動作確認テスト用のオブジェクト達。最終的に消す。
	//scythe = NewGO<GameObjectScythe>(1);

	
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