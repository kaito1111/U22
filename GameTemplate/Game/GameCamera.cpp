#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 100.0f, 100.0f, 0.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_Player = FindGO<Player>("player");
	return true;
}

void GameCamera::Update()
{
	CVector3 Target = m_Player->GetPosition();
	Target.y += 100.0f;
	CVector3 pos = Target;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//カメラの更新。
	g_camera3D.Update();
}
