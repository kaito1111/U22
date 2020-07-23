#include "stdafx.h"
#include "DebugMan.h"
#include "SampleScene.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//�S�[���̈ʒu
		//m_pos = { -358.0f,925.0f,0.0f };
		m_pos = { 0.0f, 21.0f, 0.0f };
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
		m_charaCon.Init(20.0f, 25.0f, m_pos);
	
		//�V���h�E�֘A�̏���������
		{
			//�O���t�B�b�N�X�G���W������V���h�E�}�b�v���擾
			m_shadowMap = g_graphicsEngine->GetShadowMap();
			//�e�𗎂Ƃ��J�����̍��W
			//m_lightCameraPosition = { 0.0f, 4000.0f, 0.0f };
			//�e�𗎂Ƃ������_�̍��W
			m_lightCameraTarget = CVector3::Zero();;/*CVector3::Zero();*/
		}
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		if (GetAsyncKeyState('A')) {
			m_moveSpeed.x = 5.0f;
		}
		else if(GetAsyncKeyState('D')){
			m_moveSpeed.x = -5.0f;
		}
		else {
			m_moveSpeed.x = 0;
		}
		if (GetAsyncKeyState('S')) {
			m_moveSpeed.z = 5.0f;
		}
		else if (GetAsyncKeyState('W')) {
			m_moveSpeed.z = -5.0f;
		}
		else {
			m_moveSpeed.z = 0;
		}

		m_moveSpeed.y = GRAVITY;

		//�ړ��ʌv�Z
		m_pos = m_charaCon.Execute(1.0f, m_moveSpeed);

		//���[���h�s��X�V
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::PreRender()
	{
		//�V���h�E�}�b�v�Ƀ����_�����O
		{
			//�`��ݒ�̃o�b�N�A�b�v
			//m_shadowMap->BiginRender();
			//�V���h�E�L���X�^�[�o�^
			m_shadowMap->RegistShdowCaster(&m_skinModel);
			//�V���h�E�}�b�v�p�̕`��ݒ�ɐ؂�ւ���
			//�o�^����Ă���V���h�E�L���X�^�[�̉e��`��
			//m_shadowMap->RenderToShadowMap();
			//�`��ݒ�����Ƃɖ߂�
			//m_shadowMap->EndRender();
		}
	}



	void DebugMan::Draw()
	{
		//�ʏ탌���_�����O
		{
			m_skinModel.Draw(
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix(),
				0
			);
		}
	}
}