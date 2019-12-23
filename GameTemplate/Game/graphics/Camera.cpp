#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。(のような2D)

void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//プロジェクション行列を計算。
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//スクリーンの横
		FRAME_BUFFER_H/ FRAME_BUFFER_W,	//スクリーンの高さ
		m_near,
		m_far
	);
}