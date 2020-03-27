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
	for (int p = 0; p < g_PlayerNum;p++) {
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", p + 1);
		m_Player[p] = FindGO< Player>(PlayerNo);
	}
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"Assets/modelData/Gimmick_Button.cmo", nullptr);
	m_Skin->SetPosition(m_Position);
	m_PushSkin = NewGO<SkinModelRender>(0);
	m_PushSkin->Init(L"Assets/modelData/Press_Gimmick_Button.cmo", nullptr);
	m_PushSkin->SetPosition(m_Position);
	m_PushSkin->SetActive(false);
	return true;
}

void Gimmick_Button::Update()
{
	for (int i = 0; i < g_PlayerNum; i++) {
		CVector3 Diff = m_Player[i]->GetPosition() - m_Position;
		if (Diff.Length() > 20.0f) {
			if (m_Position.y > m_Position.y + 10.0f&&
				m_Position.y < m_Position.y + 50.0f) {
				m_PushSkin->SetActive(true);
				m_Skin->SetActive(false);
				IsOn = true;
			}
		}
	}
}
