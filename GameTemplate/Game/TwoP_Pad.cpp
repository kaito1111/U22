#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"

TwoP_Pad::TwoP_Pad() {

	const int PlayerNum = 2;
	for (int i = 0; i < PlayerNum;) {
		m_pad[i].Init(i);
		CVector3 SpownPos = { 100.0f * i,0.0f,0.0f };
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", ++i);
		//�D��x���X�e�[�W���
		Player* player = NewGO<Player>(1, PlayerNo);
		player->SetPosition(SpownPos);
		player->SetPad(&m_pad[i - 1]);
		player->SetPlayerNum(i);
	}
	m_ManualSprite = NewGO<SpriteRender>(6);
	m_ManualSprite->Init(L"Assets/sprite/manual.dds", 1420.0f, 720.0f);
	m_ManualSprite->SetW(0.0f);
}
TwoP_Pad::~TwoP_Pad()
{
}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		if (IsPad) {
			m_pad[i].Update();
			//if (m_pad[i].IsTrigger(enButtonStart)) {
			//	m_ManualSprite->SetW(1.0f);
			//	IsPad = false;
			//}
		}
		//else {
		//	if (m_pad[i].IsTrigger(enButtonA)) {
		//		m_ManualSprite->SetW(0.0f);
		//		IsPad = true;
		//	}
		//}
	}
}
