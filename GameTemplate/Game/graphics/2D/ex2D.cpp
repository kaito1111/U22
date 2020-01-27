/// <summary>
/// 2D�T���v���R�[�h
/// </summary>
/// <remarks>
/// 2D�̃T���v���R�[�h�ł��B
/// NewGO�����Unitychan�̔炪�ł܂�
/// </remarks>

#include "stdafx.h"
#include "GameCamera.h"
#include "ex2D.h"

namespace myEngine {
	ex2D::ex2D()
	{
		//�X�v���C�g�����_�[�̃|�C���^
		spriteRender = NewGO<SpriteRender>(0);
		//�t�@�C���p�X�̓ǂݍ���
		spriteRender->Init(L"Assets/sprite/utc_all2.dds", 200.0f, 200.0f, false);
		//�����x�̐ݒ�
		spriteRender->SetW(0.5f);
	}


	ex2D::~ex2D()
	{
	}

	void ex2D::Update()
	{
		//���[���h���W�̍X�V
		spriteRender->Update();
	}

	void ex2D::Draw()
	{
		//�`��
		spriteRender->Draw();
	}
}
