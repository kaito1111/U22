#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"

TwoP_Pad::TwoP_Pad() {

	for (int i = 0; i < g_PlayerNum;) {
		m_pad[i].Init(i);
		CVector3 SpownPos = { 100.0f * i,0.0f,0.0f };
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", i + 1);
		//優先度をステージより
		player[i] = NewGO<Player>(1, PlayerNo);
		player[i]->SetPosition(SpownPos);
		player[i]->SetPad(&m_pad[i]);
		player[i++]->SetPlayerNum(i);
	}
	m_ManualSprite = NewGO<SpriteRender>(6);
	m_ManualSprite->Init(L"Assets/sprite/manual.dds", 1420.0f, 720.0f);
	m_ManualSprite->SetW(0.0f);
}
TwoP_Pad::~TwoP_Pad()
{
	for (int i = 0; i < g_PlayerNum;) {
		DeleteGO(player[i]);
	}
}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		m_pad[i].Update();
		if (m_pad[i].IsTrigger(enButtonStart)&&
			UpdateStop) {
			m_ManualSprite->SetW(1.0f);
			UpdateStop = false;
		}
		else {
			if (m_pad[i].IsTrigger(enButtonStart)) {
				m_ManualSprite->SetW(0.0f);
				UpdateStop = true;
			}
		}
		if (UpdateStop
			&& i < g_PlayerNum					//プレイヤーの人数分回す
			) {
			player[i]->UpDate();
		}
	}
}
