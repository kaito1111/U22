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
	if (stageNum == 0) {
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
	if (stageNum == 1) {
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

	//�e�I�u�W�F�N�g�̃X�^�[�g������܂�
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