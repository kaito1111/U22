#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"

TwoP_Pad::TwoP_Pad() {

	int i = 0;
	for (auto p : m_pad) {
		m_pad[i].Init(i);
		CVector3 SpownPos = { 100.0f * i,0.0f,0.0f };
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", ++i);
		Player* player = NewGO<Player>(1, PlayerNo);
		player->SetPosition(SpownPos);
		player->SetPad(&m_pad[i-1]);
	}
}
TwoP_Pad::~TwoP_Pad()
{
}

//bool TwoP_Pad::Start()
//{
//	return true;
//}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		m_pad[i].Update();
	}
}
