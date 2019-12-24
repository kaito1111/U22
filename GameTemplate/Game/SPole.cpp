#include "stdafx.h"
#include "SPole.h"

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
	return true;
}

void SPole::Update()
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
		CVector3 aftermove = m_player->GetPosition() - pullDir;
		m_player->SetPosition(aftermove);
	}
}