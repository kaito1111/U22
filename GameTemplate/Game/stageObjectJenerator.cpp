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
	//DeleteGO(moveFloorPtr);
}

bool stageObjectJenerator::Start()
{
	m_PointGenerator = NewGO< CheckPointgenerator>(0, "checkpointgenerator");
	//enumバグったからとりあえずintで引数渡してセレクトさせます。0番目から始まるよ
	switch (StageNum)
	{
	case 0:
		level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
		{
			//ギミック起動ボタン
			if (wcscmp(objData.name, L"Gimmick_Button") == 0) {
				moveButtonPtr = NewGO<Gimmick_Button>(0, "gimmick_button");
				moveButtonPtr->SetPosition(objData.position);
				GameObjList.push_back(moveButtonPtr);
				return true;
			}
			//動く床
			if (wcscmp(objData.name, L"moveFloor") == 0) {
				moveFloorPtr = NewGO<moveFloor>(0, "movefloor");
				moveFloorPtr->SetPosition(objData.position);
				//float型です。動かしたい量を入れてね。
				moveFloorPtr->SetMoveLimit(300.0f);
				moveFloorPtr->SetUpdate(false);
				GameObjList.push_back(moveFloorPtr);
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
				GameObjList.push_back(moveFloor2Ptr);
				return true;
			}

			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* GoalPtr = NewGO<Goal>(0, "Goal");
				GoalPtr->SetPosition(objData.position);
				GameObjList.push_back(GoalPtr);
				return true;
			}
			if (wcsstr(objData.name, L"CheckPoint") != NULL)
			{
				return true;
			}

			return false;
		});
		m_PointGenerator->Load(L"Assets/level/Corse_Level_1.tkl");
		break;
	case 1:
		//ドッスン
		level.Init(L"Assets/level/stageDossun.tkl", [&](const auto& objData)
		{
			if (wcscmp(objData.name, L"Dossun") == 0) {
				StageObjectDossun* dossunPtr = NewGO< StageObjectDossun>(0, "Dossun");
				dossunPtr->SetPosition(objData.position);
				GameObjList.push_back(dossunPtr);
				return true;
			}
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* m_GoalPtr = NewGO<Goal>(0, "Goal");
				m_GoalPtr->SetPosition(objData.position);
				GameObjList.push_back(m_GoalPtr);
			}
		});
		m_PointGenerator->Load(L"Assets/level/stageDossun.tkl");
		break;
	case 2:
		m_PointGenerator->Load(L"Assets/level/Corse_Level_2.tkl");
		level.Init(L"Assets/level/Corse_Level_2.tkl", [&](const auto& objData) {
			if (wcscmp(objData.name, L"MagnetObject") == 0) {
				Iwa* iwa = NewGO<Iwa>(0, "iwa");
				iwa->SetPosition(objData.position);
				GameObjList.push_back(iwa);
			}
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* GoalPtr = NewGO<Goal>(0, "Goal");
				GoalPtr->SetPosition(objData.position);
				GoalPtr->SetLast(true);
				GameObjList.push_back(GoalPtr);
				return true;
			}
			return true;
		});
		break;

	case 3:
		level.Init(L"Assets/level/debug_test.tkl", [&](const auto& objData) {
			//動く床
			if (wcscmp(objData.name, L"moveFloor") == 0) {
				moveFloorPtr = NewGO<moveFloor>(0, "movefloor");
				moveFloorPtr->SetPosition(objData.position);
				//float型です。動かしたい量を入れてね。
				moveFloorPtr->SetMoveLimit(300.0f);
				moveFloorPtr->SetUpdate(true);
				GameObjList.push_back(moveFloorPtr);

				return true;
			}
			if (wcsstr(objData.name, L"CheckPoint") != NULL)
			{
				return true;
			}
			//ゴール
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* GoalPtr = NewGO<Goal>(0, "Goal");
				GoalPtr->SetPosition(objData.position);
				//GoalPtr->SetLast(true);
				GameObjList.push_back(GoalPtr);
				return true;
			}
			return true;
		});
	default:
		break;
	}
	return true;
}

void stageObjectJenerator::OnDestroy()
{
	for (auto ptr : GameObjList) {
		DeleteGO(ptr);
	}
	DeleteGO(m_PointGenerator);
}



void stageObjectJenerator::Update()
{
	if (moveButtonPtr != nullptr) {
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

}