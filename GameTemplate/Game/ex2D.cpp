#include "stdafx.h"
#include "GameCamera.h"
#include "ex2D.h"

namespace myEngine {
	ex2D::ex2D()
	{
		//DDS�̍쐬
		m_tex_dummy.CreateFromDDSTextureFromFile(L"Assets/sprite/utc_all2.dds");
		//�X�v���C�g�̏�����
		m_dummy_Sprite.Init(m_tex_dummy.GetBody(), 200.0f, 200.0f);

	}


	ex2D::~ex2D()
	{
	}

	void ex2D::Update()
	{
		//m_position.x++;
		//���[���h���W�̍X�V
  		m_dummy_Sprite.Update(m_position, m_rot, m_scale);
	}

	void ex2D::Draw()
	{
		//�`��
		m_dummy_Sprite.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}
