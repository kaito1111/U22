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
	m_pad[0].Init(0);
	m_pad[1].Init(1);
	m_pad[2].Init(2);
	m_pad[3].Init(3);
	int PadNum = 0;
	QueryGOs<Player>("player", [&](Player* player)->bool {
		player->SetPad(&m_pad[PadNum]);
		PadNum++;
		return true;
	});
	return true;
}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		m_pad[i].Update();
	}
}
