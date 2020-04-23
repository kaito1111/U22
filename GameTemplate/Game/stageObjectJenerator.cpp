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
	/*enum stageNum stage;
	switch(stage) {
	case stage1:*/
	//enum�o�O��������Ƃ肠����int�ň����n���ăZ���N�g�����܂��B0�Ԗڂ���n�܂��
	if (nowStage == 0) {
		level.Init(L"Assets/level/Corse_Level_1.tkl", [&](const auto& objData)
		{
			//�M�~�b�N�N���{�^��
			if (wcscmp(objData.name, L"Gimmick_Button") == 0) {
				moveButtonPtr = NewGO<Gimmick_Button>(0, "gimmick_button");
				moveButtonPtr->SetPosition(objData.position);
				return true;
			}
			//������
			if (wcscmp(objData.name, L"moveFloor") == 0) {
				moveFloorPtr = NewGO<moveFloor>(0, "movefloor");
				moveFloorPtr->SetPosition(objData.position);
				//float�^�ł��B�����������ʂ����ĂˁB
				moveFloorPtr->SetMoveLimit(100.0f);
				return true;
			}
			//���������E�o�[�W����
			if (wcscmp(objData.name, L"moveFloor2") == 0) {
				MoveFloor2* moveFloor2Ptr = NewGO<MoveFloor2>(0, "moveFloor2");
				moveFloor2Ptr->SetPosition(objData.position);
				//float�^�ł��B�����������ʂ����ĂˁB
				moveFloorPtr->SetMoveLimit(100.0f);
				return true;
			}

			//�S�[��
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* goalPtr = NewGO<Goal>(0, "Goal");
				goalPtr->SetPosition(objData.position);
			}

			return false;
		});
	}
	
		
	

	//case stage2:
	if (nowStage == 1) {
		//�h�b�X��
		level.Init(L"Assets/level/stageDossun.tkl", [&](const auto& objData)
		{
			if (wcscmp(objData.name, L"Dossun") == 0) {
				StageObjectDossun* dossunPtr = NewGO< StageObjectDossun>(0, "Dossun");
				dossunPtr->SetPosition(objData.position);
				return true;
			}
			//�S�[��
			if (wcscmp(objData.name, L"Goal") == 0) {
				Goal* goalPtr = NewGO<Goal>(0, "Goal");
				goalPtr->SetPosition(objData.position);
			}
		});
	}
	
}


stageObjectJenerator::~stageObjectJenerator()
{
	
}

bool stageObjectJenerator::Start()
{

	
	return true;
}



void stageObjectJenerator::Update()
{
	
}

void stageObjectJenerator::Draw()
{
}