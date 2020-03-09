#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"

TwoP_Pad::TwoP_Pad() {

	int i = 0;
	const int PlayerNum = 2;
	for (int i = 0; i < PlayerNum;) {
		m_pad[i].Init(i);
		CVector3 SpownPos = { 100.0f * i,0.0f,0.0f };
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", ++i);
		//優先度をステージより
		Player* player = NewGO<Player>(1, PlayerNo);
		player->SetPosition(SpownPos);
		player->SetPad(&m_pad[i-1]);
	}
}
TwoP_Pad::~TwoP_Pad()
{
}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		m_pad[i].Update();
	}
}
