#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"

TwoP_Pad::TwoP_Pad() {

}
TwoP_Pad::~TwoP_Pad()
{
}

bool TwoP_Pad::Start()
{
	int i = 0;
	for (auto p : m_pad) {
		m_pad[i].Init(i);
		char PlayerName[256] = "player";
		char PlayerNo[256] = {};
		sprintf(PlayerNo, PlayerName, i);
		Player* player = NewGO<Player>(0, PlayerNo);
		player->SetPad(m_pad);
		i++;
	}
	return true;
}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		m_pad[i].Update();
	}
}
