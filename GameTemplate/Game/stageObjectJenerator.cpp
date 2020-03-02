#include "stdafx.h"
#include "stageObjectJenerator.h"
#include "Iwa.h"
#include"stageObject1.h"
#include"stageObject2.h"
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
}

bool stageObjectJenerator::Start()
{
	level.Init(L"Assets/level/stage_iwa.tkl", [&](const auto& objData)
	{
		if (wcscmp(objData.name, L"iwa.cmo") == 0) {

			auto IwaPtr = new Iwa(
				L"Assets/modelData/iwa.cmo",
				objData.position,
				objData.rotation);
			IwaList.push_back(IwaPtr);
			return true;
		}
		return false;
	});

	//オブジェクトのNewGO
	//object1 = NewGO<stageObject1>(1, "object1");
	//object2 = NewGO<stageObject2>(1, "object2");//現在バグなう。追加しないでね。
	movefloor = NewGO<moveFloor>(1, "movefloor");
	rorlingRock = NewGO<RorlingRock>(1, "rorlingRock");
	scythe = NewGO<GameObjectScythe>(1, "scythe");
	dossun = NewGO< StageObjectDossun>(1, "dossun");
	magma = NewGO< StageObjectMagma>(1, "magma");
	return true;
}

void stageObjectJenerator::Update()
{
	level.Draw();
	for (auto& i : IwaList) {
		i->Update();
		i->Draw();
	}
}