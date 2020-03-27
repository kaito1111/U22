#include "stdafx.h"
#include "TitleCamera.h"

TitleCamera::TitleCamera()
{
}

TitleCamera::~TitleCamera()
{
}

bool TitleCamera::Start()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 0.0f, -500.0f });
	g_camera3D.SetTarget(CVector3::Zero());
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	return true;
}

void TitleCamera::Update()
{
	CVector3 Target = CVector3::Zero();
	CVector3 pos = {0.0f,2000.0f,5000.0f};
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//カメラの更新。
	g_camera3D.Update();
}