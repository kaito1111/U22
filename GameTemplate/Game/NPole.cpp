#include "stdafx.h"
#include "NPole.h"

NPole::NPole()
{
	m_model.Init(L"Assets/modelData/NPole.cmo");
}

NPole::~NPole()
{
}

bool NPole::Start()
{
	m_player = FindGO<Player>("plaayer");
	m_move = m_player->GetForward();
	return true;
}

void NPole::Update()
{
	m_position += m_move;
	deleteTime++;
	if (deleteTime >= 1800)
	{
		DeleteGO(this);
	}
	CVector3 pullDir = m_player->GetPosition() - m_position;
	if (pullDir.Length() < 50.0f)
	{
		pullDir.Normalize();
		m_position -= pullDir * 0.1f;
	}
	
}
