#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。(のような2D)
//Camera g_camera2D;		//2Dカメラ

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
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//スクリーンの横
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//スクリーンの高さ
		m_near, 
		m_far
	);
}