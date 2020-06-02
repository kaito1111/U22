#include "stdafx.h"
#include "StageSelect/TitleCamera.h"
#include "Player.h"
TitleCamera::TitleCamera()
{
}

TitleCamera::~TitleCamera()
{
}

bool TitleCamera::Start()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 10.0f, 500.0f });
	g_camera3D.SetTarget(CVector3::Zero());
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	player = FindGO<Player>("player1");
	return true;
}

void TitleCamera::Update()
{
	CVector3 Target = player->GetPosition();
	CVector3 pos = player->GetPosition();
	pos.y += 500.0f;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//カメラの更新。
	g_camera3D.Update();
}