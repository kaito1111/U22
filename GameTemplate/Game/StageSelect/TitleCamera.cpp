#include "stdafx.h"
#include "StageSelect/TitleCamera.h"
#include "Player.h"
TitleCamera::TitleCamera()
{
	int a = 0;
}

TitleCamera::~TitleCamera()
{
	int a = 0;
}

bool TitleCamera::Start()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 50.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 500.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	//player = FindGO<GamePlayer>("player1");
	return true;
}

void TitleCamera::Update()
{
	CVector3 Target = { -800.0f,600.0f,0.0f };
	CVector3 pos = Target;
	pos.y += 100.0;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//カメラの更新。
	g_camera3D.Update();
}