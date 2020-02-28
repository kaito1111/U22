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
	m_position = m_player->GetPosition();
	return true;
}

void SPole::Update()
{
	idou();
	deleteRange();
	SetSPole();
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
	if (playerDir.Length() > 10000.0f) {
		DeleteGO(this);
	}
}
//
//void SPole::magunetTask(CVector3& Position)
//{
//	CVector3 pullDir = Position - m_position;
//	if (pullDir.Length() < 50.0f) {
//		pullDir.Normalize();
//		Position -= pullDir;
//	}
//}

void SPole::idou()
{
	//CVector3 oldPos = m_position;
	//float diff = oldPos.Length() - m_position.Length();
	//if (0.001f > diff && -0.001f < diff) {
	//	//magunetTask(m_position);
	//}
	m_move.Normalize();
	m_position += m_move;
}

void SPole::SetSPole() {
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