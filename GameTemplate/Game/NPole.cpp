#include "stdafx.h"
#include "NPole.h"

#include "Player.h"

NPole::NPole()
{
	m_model.Init(L"Assets/modelData/NPole.cmo");
	m_CharaCon.Init(10.0f, 10.0f, m_position);
}

NPole::~NPole()
{
}

bool NPole::Start()
{
	m_player = FindGO<Player>("player");
	m_position = m_player->GetPosition();
	m_position.y += 20.0f;
	m_CharaCon.Init(10.0f, 10.0f, m_position);
	return true;
}

void NPole::Update()
{
	m_position += m_move;

	CVector3 pullDir = m_player->GetPosition() - m_position;
	if (pullDir.Length() > 100.0f) {
		DeleteGO(this);
	}

	if (pullDir.Length() < 50.0f)
	{
		pullDir.Normalize();
		CVector3 aftermove = m_player->GetPosition() - pullDir;
		m_player->SetPosition(aftermove);
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