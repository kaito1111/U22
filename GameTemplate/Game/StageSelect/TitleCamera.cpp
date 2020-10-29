#include "stdafx.h"
#include "StageSelect/TitleCamera.h"
#include "Player.h"
#include "StageSelect.h"
TitleCamera::TitleCamera()
{
}

TitleCamera::~TitleCamera()
{
}

bool TitleCamera::Start()
{
	m_Target.y += 50.0f;
	m_Pos = m_Target;
	m_Pos.z += 500.0f;
	//カメラを初期化。
	g_camera3D.SetPosition(m_Pos);
	g_camera3D.SetTarget(m_Target);
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	return true;
}

void TitleCamera::Update()
{
	Move();//移動関係

	//座標とかの更新
	g_camera3D.SetTarget(m_Target); 
	g_camera3D.SetPosition(m_Pos);
	g_camera3D.Update();
}

void TitleCamera::Move()
{
	m_Target.y += 100.0f;
	m_Pos = m_Target;
	m_Pos.z += 500.0f;
}
