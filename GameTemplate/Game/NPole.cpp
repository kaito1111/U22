#include "stdafx.h"
#include "NPole.h"

#include "Player.h"

NPole::NPole()
{
	QueryGOs<NPole>("npole", [&](NPole* pole)->bool {
		DeleteGO(pole); 
		return true;
	});
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
