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
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 10.0f, 500.0f });
	g_camera3D.SetTarget(CVector3::Zero());
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	//player = FindGO<GamePlayer>("player1");
	return true;
}

void TitleCamera::Update()
{
	CVector3 Target = { 0.0f,100.0f,0.0f };
	CVector3 pos = Target;
	pos.y += 200.0f;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//�J�����̍X�V�B
	g_camera3D.Update();
}