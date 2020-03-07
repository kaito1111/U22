#include "stdafx.h"
#include "stageObjectJenerator.h"
#include "Iwa.h"
#include"stageObject1.h"
#include"moveFloor.h"
#include"RorlingRock.h"
#include"GameObjectScythe.h"
#include"StageObjectDossun.h"
#include"StageObjectMagma.h"
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
}

bool stageObjectJenerator::Start()
{
	level.Init(L"Assets/level/stageLevel.tkl", [&](const auto& objData)
	{
		//��
		if (wcscmp(objData.name, L"iwa") == 0) {
			auto IwaPtr = new Iwa(
				L"Assets/modelData/iwa.cmo",
				objData.position,
				objData.rotation);
			IwaList.push_back(IwaPtr);
			return true;
		}
		//������
		if (wcscmp(objData.name, L"moveFloor") == 0) {
			auto moveFloorPtr = new moveFloor(
				L"Assets/modelData/iwa.cmo",
				objData.position,
				objData.rotation);
			moveFloorList.push_back(moveFloorPtr);
			return true;
		}
		//��銙
		if (wcscmp(objData.name, L"Huriko") == 0) {
			auto GameObjectScythePtr = new GameObjectScythe(
				L"Assets/modelData/Huriko.cmo",
				objData.position,
				objData.rotation);
			GameObjectScytheList.push_back(GameObjectScythePtr);
			return true;
		}
		////�h�b�X��
		//if (wcscmp(objData.name, L"Dossun") == 0) {
		//	auto StageObjectDossunPtr = new StageObjectDossun(
		//		L"Assets/modelData/Dossun.cmo",
		//		objData.position,
		//		objData.rotation);
		//	StageObjectDossunList.push_back(StageObjectDossunPtr);
		//	return true;
		//}
		////�����点�肠�����Ă��鉽��
		//if (wcscmp(objData.name, L"magma") == 0) {
		//	auto StageObjectMagmaPtr = new StageObjectMagma(
		//		L"Assets/modelData/magma.cmo",
		//		objData.position,
		//		objData.rotation);
		//	StageObjectMagmaList.push_back(StageObjectMagmaPtr);
		//	return true;
		//}
		return false;
	});

	//�I�u�W�F�N�g��NewGO
	//object1 = NewGO<stageObject1>(1, "object1");
	//object2 = NewGO<stageObject2>(1, "object2");//���݃o�O�Ȃ��B�ǉ����Ȃ��łˁB
	//movefloor = NewGO<moveFloor>(1, "movefloor");
	//rorlingRock = NewGO<RorlingRock>(1, "rorlingRock");
	//scythe = NewGO<GameObjectScythe>(1, "scythe");
	//dossun = NewGO< StageObjectDossun>(1, "dossun");
	//magma = NewGO< StageObjectMagma>(1, "magma");
	return true;
}

void stageObjectJenerator::Update()
{
	level.Draw();
	for (auto& i : IwaList) {
		i->Update();
		i->Draw();
	}
	for (auto& i : moveFloorList) {
		i->Update();
		i->Draw();
	}
	for (auto& i : GameObjectScytheList) {
		i->Update();
		i->Draw();
	}
	for (auto& i : StageObjectDossunList) {
		i->Update();
		i->Draw();
	}
	for (auto& i : StageObjectMagmaList) {
		i->Update();
		i->Draw();
	}
}