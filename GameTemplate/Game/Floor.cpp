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
	//�ÓI�������W�F�N�g
	atariHantei.CreateMeshObject(m_model, m_pos, CQuaternion::Identity());

}
