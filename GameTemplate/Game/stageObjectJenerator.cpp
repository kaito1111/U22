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
#include "CheckPointgenerator.h"
stageObjectJenerator::stageObjectJenerator()
{
	
}


stageObjectJenerator::~stageObjectJenerator()
{
}

bool stageObjectJenerator::Start()
{
	//enumバグったからとりあえずintで引数渡してセレクトさせます。0番目から始まるよ
	if (StageNum == 0) {
		level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
		{
			//ギミック起動ボタン
			if (wcscmp(objData.name, L"Gimmick_Button") == 0) {
				moveButtonPtr = NewGO<Gimmick_Button>(0, "gimmick_button");
				moveButtonPtr->SetPosition(objData.position);
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
				Floor2PosX = moveFloor2Ptr->GetPosition().x;
				Floor2PosX -= 200.0f;
				return true;
			}

			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				m_goalPtr = NewGO<Goal>(0, "Goal");
				m_goalPtr->SetPosition(objData.position);
				return true;
			}
			if (wcsstr(objData.name, L"CheckPoint") != NULL)
			{
				return true;
			}
			CheckPointgenerator* PointGenerator = NewGO< CheckPointgenerator>(0, "checkpointgenerator");
			PointGenerator->Load(L"Assets/level/Corse_Level_1.tkl");

			return false;
		});
	}




	//case stage2:
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
			CheckPointgenerator* PointGenerator = NewGO< CheckPointgenerator>(0, "checkpointgenerator");
			PointGenerator->Load(L"Assets/level/stageDossun.tkl");
		});
	}
	return true;
}



void stageObjectJenerator::Update()
{
	if (moveButtonPtr->IsOn()) {
		if (moveFloor2Ptr->GetPosition().x > Floor2PosX) {
			moveFloor2Ptr->SetUpdate(true);
			moveFloorPtr->SetUpdate(true);
		}
		else {
			moveFloor2Ptr->SetUpdate(false);
		}
	}
	
}

void stageObjectJenerator::Draw()
{
}