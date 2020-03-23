#include "stdafx.h"
#include "DebugMan.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//�S�[���̈ʒu
		//m_pos = { -358.0f,925.0f,0.0f };
		m_pos = CVector3::Zero();
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
	
		//�V���h�E�֘A�̏���������
		{
			//�O���t�B�b�N�X�G���W������V���h�E�}�b�v���擾
			m_shadowMap = g_graphicsEngine->GetShadowMap();
			//�e�𗎂Ƃ��J�����̍��W
			m_lightCameraPosition = { 0.0f, 4000.0f, 0.0f };
			//�e�𗎂Ƃ������_�̍��W
			m_lightCameraTarget = CVector3::Zero();;/*CVector3::Zero();*/
		}
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//�V���h�E�֘A�̍X�V����
		{
			//�V���h�E�L���X�^�[�o�^
			m_shadowMap->RegistShdowCaster(&m_skinModel);
			//���C�g�̍��W���X�V
			m_shadowMap->UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
		}

		if (GetAsyncKeyState('A')) {
			m_pos.x += 5;
		}
		else if(GetAsyncKeyState('D')){
			m_pos.x -= 5;
		}

		//���[���h�s��X�V
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::PreRender()
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