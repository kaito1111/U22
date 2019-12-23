#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B(�̂悤��2D)

void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//�v���W�F�N�V�����s����v�Z�B
	m_projMatrix.MakeOrthoProjectionMatrix(
		FRAME_BUFFER_W,					//�X�N���[���̉�
		FRAME_BUFFER_H,	//�X�N���[���̍���
		m_near,
		m_far
	);
}