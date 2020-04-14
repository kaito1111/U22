#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"


TwoP_Pad::TwoP_Pad() {

	for (int i = 0; i < Pad::CONNECT_PAD_MAX;i++) {
		g_Pad[i].Init(i);
	}
	m_ManualSprite = NewGO<SpriteRender>(6);
	m_ManualSprite->Init(L"Assets/sprite/manual.dds", 1420.0f, 720.0f);
	m_ManualSprite->SetW(1.0f);
}
TwoP_Pad::~TwoP_Pad()
{
	//for (int i = 0; i < g_PlayerNum;i++) {
	//	DeleteGO(player[i]);
	//}
	DeleteGO(m_ManualSprite);
}

//bool TwoP_Pad::Start()
//{
//
//		return true;
//	
//	return false;
//}

void TwoP_Pad::Update()
{
	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
		g_Pad[i].Update();
		if (i < g_PlayerNum) {
			if (g_Pad[i].IsTrigger(enButtonStart) 
				//&&player[i]->GetUpdate()
				) {
				m_ManualSprite->SetW(1.0f);
				//player[i]->SetUpdate(false);
			}
			else {
				if (g_Pad[i].IsTrigger(enButtonStart)) {
					m_ManualSprite->SetW(0.0f);
					//player[i]->SetUpdate(true);
				}
			}
		}
	}
}
