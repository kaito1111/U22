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
	m_position = m_SpownPos;
	m_position.y += 50.0f;
	return true;
}

void NPole::Update()
{
	Move();
	SetNPole();
	deleteRange();
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

void NPole::deleteRange()
{
	CVector3 playerDir = m_SpownPos - m_position;
	if (playerDir.Length() > 200.0f) {
		DeleteGO(this);
	}
}

void NPole::Move()
{
	m_move.Normalize();
	m_position += m_move;
}

void NPole::SetNPole() {
	QueryMO([&](Magnet* m_Magnet)->bool
	{
		CVector3 Diff = m_Magnet->GetPosition() - m_position;
		float ModeJudge = 100.0f;
		if (Diff.Length() < ModeJudge) {
			if (m_Magnet->IsChenge() == true) {
				m_Magnet->SetState(Magnet::State::NMode);
			}
		}
		return true;
	});
}