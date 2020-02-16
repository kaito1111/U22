#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B(�̂悤��2D)
Camera g_camera2D;		//2D�J����

Camera::Camera():
	m_near(0.1f),
	m_far(5000.0f),
	m_position(CVector3::Zero()),
	m_target(CVector3{0,0,1}),
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
	
//�v���W�F�N�V�����s��
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//�X�N���[���̉�
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//�X�N���[���̍���
		m_near, 
		m_far
	);
}

void Camera::Update2D()
{
	g_camera2D.SetPosition({ 0.0f,0.0f,-10.0f });
	g_camera2D.SetTarget({ 0.0,0.0,0.0 });

	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	m_projMatrix.MakeOrthoProjectionMatrix(FRAME_BUFFER_W, FRAME_BUFFER_H, m_near, m_far);
}