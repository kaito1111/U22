#include "stdafx.h"
#include "stageObjectJenerator.h"
#include "stageObject/Iwa.h"
#include"stageObject/stageObject1.h"
#include"stageObject/moveFloor.h"
#include"stageObject/RorlingRock.h"
#include"stageObject/GameObjectScythe.h"
#include"stageObject/StageObjectDossun.h"
#include"stageObject/StageObjectMagma.h"
#include"stageObject/Goal.h"
#include "stageObject/Gimmick_Button.h"
#include"stageObject/MoveFloor2.h"
stageObjectJenerator::stageObjectJenerator()
{
	if (StageNum == 0) {
		level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
		{
			//ギミック起動ボタン
			if (wcscmp(objData.name, L"Gimmick_Button") == 0) {
				moveButtonPtr = NewGO<Gimmick_Button>(0, "gimmick_button");
				moveButtonPtr->SetPosition(/*CVector3::Zero()*/objData.position);
				return true;
			}
			//動く床
			if (wcscmp(objData.name, L"moveFloor") == 0) {
				moveFloorPtr = NewGO<moveFloor>(0, "movefloor");
				moveFloorPtr->SetPosition(objData.position);
				//float型です。動かしたい量を入れてね。
				moveFloorPtr->SetMoveLimit(300.0f);
				moveFloorPtr->SetUpdate(false);
				return true;
			}
			//動く床左右バージョン
			if (wcscmp(objData.name, L"moveFloor2") == 0) {
				moveFloor2Ptr = NewGO<MoveFloor2>(0, "moveFloor2");
				moveFloor2Ptr->SetPosition(objData.position);
				//float型です。動かしたい量を入れてね。
				moveFloor2Ptr->SetMoveLimit(100.0f);
				moveFloor2Ptr->SetUpdate(false);
				return true;
			}
			
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* goalPtr = NewGO<Goal>(0, "Goal");
				goalPtr->SetPosition(objData.position);
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
	if (StageNum == 0) {
		if (moveButtonPtr->GetOn()) {
				moveFloor2Ptr->SetUpdate(true);
			if (moveFloor2Ptr->GetPosition().x < -100.0f) {
				moveFloor2Ptr->SetUpdate(false);
			}
			moveFloorPtr->SetUpdate(true);
		}
	}
	//level.Draw();
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