#include "stdafx.h"
#include "DebugMan.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		m_shadowMap = g_graphicsEngine->GetShadowMap();
		//�S�[���̈ʒu
		//m_pos = { -358.0f,925.0f,0.0f };
		m_pos = CVector3::Zero();
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
		//�e�𗎂Ƃ��J�����̍��W
		m_lightCameraPosition = { 0.0f, 2000.0f, 0.0f };
		//�e�𗎂Ƃ������_�̍��W
		m_lightCameraTarget = m_pos;/*CVector3::Zero();*/
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//�V���h�E�L���X�^�[�o�^
		m_shadowMap->RegistShdowCaster(&m_skinModel);
		//���C�g�̍��W���X�V
		m_shadowMap->UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
		//���[���h�s��X�V
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::Render()
	{
		//�V���h�E�}�b�v�Ƀ����_�����O
		{
			//�`��ݒ�̃o�b�N�A�b�v
			m_shadowMap->BiginRender();
			//�V���h�E�}�b�v�p�̕`��ݒ�ɐ؂�ւ���
			//�o�^����Ă���V���h�E�L���X�^�[�̉e��`��
			m_shadowMap->RenderToShadowMap();
			//�`��ݒ�����Ƃɖ߂�
			m_shadowMap->EndRender();
		}
	}



	void DebugMan::Draw()
	{
		//�ʏ탌���_�����O
		{
			m_skinModel.Draw(
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix(),
				0,
				g_graphicsEngine->GetShadowMap()->GetLightViewMatirx(),
				g_graphicsEngine->GetShadowMap()->GetLightProjMatirx()
			);
		}
	}
}