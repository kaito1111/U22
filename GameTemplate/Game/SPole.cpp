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
	m_player = FindGO<Player>("player");
	m_position.y += 20.0f;
	m_characon.Init(10.0f, 10.0f, m_position);
	m_npole = FindGO<NPole>("npole");
	return true;
}

void SPole::Update()
{
	m_position += m_move;
	CVector3 playerDir = m_player->GetPosition - m_position;
	if (playerDir.Length() > 100.0f) {
		DeleteGO(this);
	}

	CVector3 pullDir = m_npole->GetPosition() - m_position;
	if (pullDir.Length() < 50.0f)
	{
		pullDir.Normalize();
		CVector3 aftermove = m_npole->GetPosition() - pullDir;
		m_npole->SetPosition(aftermove);
	}

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
