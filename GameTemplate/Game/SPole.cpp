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
	m_move = m_player->GetForward(); 
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
}
