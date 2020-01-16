#include "stdafx.h"
#include "NPole.h"

#include "Player.h"

NPole::NPole()
{
	m_model.Init(L"Assets/modelData/NPole.cmo");
}

NPole::~NPole()
{
}

bool NPole::Start()
{
	m_player = FindGO<Player>("player");
	m_position.y += 20.0f;
	m_characon.Init(10.0f, 10.0f, m_position);
	return true;
}

void NPole::Update()
{
	m_position = m_characon.Execute(1.0f,m_move);

	CVector3 pullDir = m_player->GetPosition() - m_position;
	//if (pullDir.Length() > 100.0f) {
	//	DeleteGO(this);
	//}

	if (pullDir.Length() < 50.0f){
		pullDir.Normalize();
		CVector3 aftermove = m_player->GetPosition() - pullDir;
		m_player->SetPosition(aftermove);
	}
	if (m_player->GetMagnetNum() == 1) {				//1はS極
		CVector3 playerDir = m_player->GetPosition() - m_position;
		playerDir.Normalize();
		CVector3 SetPlayerPos = m_player->GetPosition() - playerDir;
		m_player->SetPosition(SetPlayerPos);
		m_move += playerDir;
	}
	if (m_player->GetMagnetNum() == 2) {				//2はN極
		CVector3 playerDir = m_player->GetPosition() - m_position;
		playerDir.Normalize();
		CVector3 SetPlayerPos = m_player->GetPosition() + playerDir;	//プレイヤーを離す
		m_player->SetPosition(SetPlayerPos);
		m_move -= playerDir;
	}

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void NPole::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}