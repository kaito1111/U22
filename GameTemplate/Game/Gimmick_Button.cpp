#include "stdafx.h"
#include "Gimmick_Button.h"

Gimmick_Button::Gimmick_Button()
{
}

Gimmick_Button::~Gimmick_Button()
{
}

bool Gimmick_Button::Start()
{
	for (int p = 0; p < g_PlayerNum;) {
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", p + 1);
		m_Player[p] = FindGO< Player>(PlayerNo);
	}
	m_Skin.Init(L"Assets/modelData/Gimmick_Button.cmo");
	m_PushSkin.Init(L"Assets/modelData/Press_Gimmick_Button.cmo");
	m_PushSkin.
	return true;
}

void Gimmick_Button::Update()
{

}
