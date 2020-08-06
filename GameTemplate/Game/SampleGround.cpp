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
	//���f��������
	skin = NewGO<SkinModelRender>(0);
	skin->Init(L"testGround.cmo");
	//�V���h�E���V�[�o�[�ɐݒ�
	skin->GetSkinModel().SetShadowReciever(true);
	//�����蔻��쐬
	physicsGround.CreateMeshObject(skin->GetSkinModel(), pos, qRot);
	return true;
}

void SampleGround::Update()
{
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();
	//m_shadowMap->RegistShdowCaster(&skin->GetSkinModel());
}
