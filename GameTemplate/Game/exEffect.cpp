/// <summary>
/// �G�t�F�N�g�Đ��̃T���v���R�[�h
/// </summary>

#include "stdafx.h"
#include "exEffect.h"
#include "Effect.h"

exEffect::exEffect()
{
	//�Đ�&������
	effect->Play(L"Assets/effect/test.efk");
	effect->SetScale(CVector3::One() * 10);
}

exEffect::~exEffect()
{
	//DeleteGO(this);
}

void exEffect::Update()
{
	//�f�o�b�O�p�̃R�[�h
	CVector3 ePos = m_pos;
	ePos = player->GetPosition();
	//ePos.y += 150;
	effect->SetPosition(ePos);
}
