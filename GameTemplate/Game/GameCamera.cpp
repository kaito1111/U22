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
	QueryGOs<Player>("player", [&](Player* player)->bool {

		m_Player[m_PlayerNum] = player;
		m_PlayerNum++;
		return true;
	});
	return true;
}

void GameCamera::Update()
{
	CVector3 Target = CVector3::Zero();
	for (int i = 0; i < m_PlayerNum; i++) {
		Target += m_Player[i]->GetPosition();
		Target.y += 100.0f;
	}
	Target /= (int)m_PlayerNum;
	if (Decline < Target.y) {
		Decline = Target.y;
	}
	else {
		Target.y = Decline;
	}
	CVector3 pos = Target;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(pos);
	//カメラの更新。
	g_camera3D.Update();
}
