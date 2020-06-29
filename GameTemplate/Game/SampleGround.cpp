#include "stdafx.h"
#include "SampleGround.h"

SampleGround::SampleGround()
{
}

SampleGround::~SampleGround()
{
}

bool SampleGround::Start()
{
	skin = NewGO<SkinModelRender>(0);
	skin->Init(L"Assets/modelData/testGround.cmo");
	physicsGround.CreateMeshObject(skin->GetSkinModel(), pos, qRot);
	skin->GetSkinModel().SetShadowReciever(true);

	return true;
}

void SampleGround::Update()
{
}
