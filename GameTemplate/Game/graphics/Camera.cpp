#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B(�̂悤��2D)
//Camera g_camera2D;		//2D�J����

Camera::Camera():
	m_near(0.1f),
	m_far(5000.0f),
	m_position(CVector3::Zero()),
	m_up(CVector3::Up()),
	m_aspect(1.0f)
{
}


void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

	//�v���W�F�N�V�����s����v�Z
	m_projMatrix.MakeOrthoProjectionMatrix(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		m_near,
		m_far
	);

	/*
	���Ȃ�2D�����̂�MakeOrtho�̂������̗p��
	���R�������莟�撼����tkEngine�̕��ɏ��������킹�܂�
	*/

	//m_projMatrix.MakeProjectionMatrix(
	//	m_viewAngle,					//�X�N���[���̉�
	//	FRAME_BUFFER_W / FRAME_BUFFER_H,	//�X�N���[���̍���
	//	m_near, 
	//	m_far
	//);
}