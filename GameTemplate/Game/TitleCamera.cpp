#include "stdafx.h"
#include "TitleCamera.h"


TitleCamera::TitleCamera()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ -300.0f, 100.0f, 1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}


TitleCamera::~TitleCamera()
{
	
}

bool TitleCamera::Start()
{
	return true;
}

void TitleCamera::Update()
{
	CVector3 Target = CVector3::Zero();
	CVector3 pos = {0.0f,500.0f,500.0f};
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//カメラの更新。
	g_camera3D.Update();
}