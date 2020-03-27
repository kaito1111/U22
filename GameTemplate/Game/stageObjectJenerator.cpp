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
#include "Gimmick_Button.h"
stageObjectJenerator::stageObjectJenerator()
{
	if (StageNum == 0) {
		level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
		{
			//動く床
			if (wcscmp(objData.name, L"moveFloor") == 0) {
				moveFloor* moveFloorPtr = NewGO<moveFloor>(0, "movefloor");
				moveFloorPtr->SetPosition(objData.position);
				return true;
			}
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* goalPtr = NewGO<Goal>(0, "Goal");
				goalPtr->SetPosition(objData.position);
			}
			//ギミック起動ボタン
			if (wcscmp(objData.name, L"Gimmick_Button") == 0) {
				Gimmick_Button* moveButtonPtr = NewGO< Gimmick_Button>(0, "gimmick_button");
				moveButtonPtr->SetPosition(objData.position);
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
				StageObjectDossun* dossunPtr = NewGO< StageObjectDossun>(0, "Dossun");
				dossunPtr->SetPosition(objData.position);
				return true;
			}
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* goalPtr = NewGO<Goal>(0, "Goal");
				goalPtr->SetPosition(objData.position);
			}
		});
	}
}


stageObjectJenerator::~stageObjectJenerator()
{
	/*for (auto i : IwaList) {
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
	}*/
}

bool stageObjectJenerator::Start()
{

	//各オブジェクトのスタートが走ります
	/*for (auto& i : IwaList) {
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
	}*/
	return true;
}



void stageObjectJenerator::Update()
{
	level.Draw();
	/*for (auto& i : IwaList) {
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
	}*/
}

void stageObjectJenerator::Draw()
{
	/*for (auto& i : IwaList) {
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
	}*/
}