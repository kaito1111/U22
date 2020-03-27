#include "stdafx.h"
#include "Floor.h"


Floor::Floor()
{
}
Floor::~Floor()
{
}

bool Floor::Start()
{
	m_model.Init(L"Assets/modelData/bStopFloor.cmo");

	return true;
}

void Floor::Update()
{
	//静的物理部ジェクト
	atariHantei.CreateMeshObject(m_model, m_pos, CQuaternion::Identity());

}
