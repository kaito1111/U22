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

	//�G�t�F�N�g�̃C���X�^���X
	m_effect1 = NewGO<Effect>(0);
	m_effect2 = NewGO<Effect>(0);

	//�����蔻��쐬
	physicsGround.CreateMeshObject(skin->GetSkinModel(), pos, qRot);
	return true;
}

void SampleGround::Update()
{
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();

	m_effect1->SetPosition({ 100, 10, 0 });
	m_effect1->SetScale(CVector3::One() * 10.0f);
	m_effect1->Play(L"Assets/effect/test.efk");
	m_effect2->SetPosition({ 200, 10, 0 });
	m_effect2->SetScale(CVector3::One() * 10.0f);
	m_effect2->Play(L"Assets/effect/test.efk");
	//m_shadowMap->RegistShdowCaster(&skin->GetSkinModel());
}
