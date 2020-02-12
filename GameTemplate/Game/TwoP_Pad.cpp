#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"

TwoP_Pad::TwoP_Pad() {

	int i = 0;
	for (auto p : m_pad) {
		m_pad[i].Init(i);
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", i+1);
		Player* player = NewGO<Player>(1, PlayerNo);
		player->SetPad(&m_pad[i]);
		i++;
	}
}
TwoP_Pad::~TwoP_Pad()
{
}

bool TwoP_Pad::Start()
{
	return true;
}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		m_pad[i].Update();
	}
}
