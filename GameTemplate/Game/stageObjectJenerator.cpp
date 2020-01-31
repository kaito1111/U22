#include "stdafx.h"
#include "stageObjectJenerator.h"
#include "Iwa.h"


stageObjectJenerator::stageObjectJenerator()
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
}


stageObjectJenerator::~stageObjectJenerator()
{
	for (auto i : IwaList) {
		delete i;
	}
}

void stageObjectJenerator::Update()
{
	int a = 0;
	level.Draw();
	for (auto& i : IwaList) {
		i->Update();
		i->Draw();
	}
}