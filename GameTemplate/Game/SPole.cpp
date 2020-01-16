#include "stdafx.h"
#include "SPole.h"

#include "NPole.h"
#include "Player.h"

SPole::SPole()
{
	m_model.Init(L"Assets/modelData/SPole.cmo");
}

SPole::~SPole()
{
}

bool SPole::Start()
{
	m_npole = FindGO<NPole>("npole");
	m_player = FindGO<Player>("player");
	m_position.y += 20.0f;
	m_characon.Init(10.0f, 10.0f, m_position);
	return true;
}

void SPole::Update()
{
	idou();
	//deleteRange();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void SPole::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void SPole::deleteRange()
{
	CVector3 playerDir = m_player->GetPosition() - m_position;
	if (playerDir.Length() > 100.0f) {
		DeleteGO(this);
	}
}

void SPole::magunetTask()
{
	CVector3 pullDir = m_npole->GetPosition() - m_position;
	if (pullDir.Length() < 50.0f) {
		pullDir.Normalize();
		CVector3 aftermove = m_npole->GetPosition() - pullDir;
		m_npole->SetPosition(aftermove);
		if (m_player->GetMagnetNum() == 1) {				//1はS極
			CVector3 playerDir = m_player->GetPosition() - m_position;
			playerDir.Normalize();
			CVector3 SetPlayerPos = m_player->GetPosition() + playerDir;	//プレイヤーを離す
			m_player->SetPosition(SetPlayerPos);
			m_move -= playerDir;
		}
		if (m_player->GetMagnetNum() == 2) {				//2はN極
			CVector3 playerDir = m_player->GetPosition() - m_position;
			playerDir.Normalize();
			CVector3 SetPlayerPos = m_player->GetPosition() - playerDir;
			m_player->SetPosition(SetPlayerPos);
			m_move += playerDir;
		}
	}
}

void SPole::idou()
{
	CVector3 oldPos = m_position;
	m_position = m_characon.Execute(1.0f, m_move);
	float diff = oldPos.Length() - m_position.Length();
	if (0.001f > diff && -0.001f < diff) {
		magunetTask();
	}
}
