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
	return true;
}

void NPole::Update()
{
	//CVector3 pullDir = m_player->GetPosition() - m_position;
	//if (pullDir.Length() > 100.0f) {
	//	DeleteGO(this);
	//}

	//if (pullDir.Length() < 50.0f){
	//	pullDir.Normalize();
	//	CVector3 aftermove = m_player->GetPosition() - pullDir;
	//	m_player->SetPosition(aftermove);
	//}
	//if (m_player->GetMagnetNum() == 1) {				//1はS極
	//	CVector3 playerDir = m_player->GetPosition() - m_position;
	//	playerDir.Normalize();
	//	CVector3 SetPlayerPos = m_player->GetPosition() - playerDir;
	//	m_player->SetPosition(SetPlayerPos);
	//	m_move += playerDir;
	//}
	//if (m_player->GetMagnetNum() == 2) {				//2はN極
	//	CVector3 playerDir = m_player->GetPosition() - m_position;
	//	playerDir.Normalize();
	//	CVector3 SetPlayerPos = m_player->GetPosition() + playerDir;	//プレイヤーを離す
	//	m_player->SetPosition(SetPlayerPos);
	//	m_move -= playerDir;
	//}
	SetNPole();
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

void NPole::SetNPole() {
	QueryMO([&](Magnet* m_Magnet)->bool
	{
		CVector3 Diff = m_Magnet->GetPosition() - m_position;
		const CVector3 ModeJudge = { 200.0f,200.0f,200.0f };
		if (Diff.Length() < ModeJudge.Length()) {
			m_Magnet->SetState(Magnet::State::SMode);
		}
		return true;
	});
}