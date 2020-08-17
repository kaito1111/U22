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
	m_position = m_SpownPos;
	m_position.y += 50.0f;
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
	CVector3 playerDir = m_SpownPos - m_position;
	if (playerDir.Length() > 200.0f) {
		DeleteGO(this);
	}
}

void SPole::idou()
{
	m_move.Normalize();
	m_position += m_move;
}

void SPole::SetSPole() {
	QueryMO([&](Magnet* m_Magnet)->bool
	{
		CVector3 Diff = m_Magnet->GetPosition() - m_position;
		float ModeJudge = 100.0f;
		if (Diff.Length() < ModeJudge) {
			if (m_Magnet->IsChenge() == true) {
				m_Magnet->SetState(Magnet::State::SMode);
			}
		}
		return true;
	});
}