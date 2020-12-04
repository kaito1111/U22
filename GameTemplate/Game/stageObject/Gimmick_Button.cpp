#include "stdafx.h"
#include "Gimmick_Button.h"

Gimmick_Button::Gimmick_Button()
{
	m_Se.Init(L"Assets/sound/Button_On.wav");
}

Gimmick_Button::~Gimmick_Button()
{
}

void Gimmick_Button::OnDestroy()
{
	DeleteGO(m_Skin);
	DeleteGO(m_PushSkin);
}

bool Gimmick_Button::Start()
{
	for (int p = 0; p < g_PlayerNum;p++) {
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", p + 1);
		m_Player[p] = FindGO<GamePlayer>(PlayerNo);
	}
	m_Skin = NewGO<SkinModelRender>(0);
	m_Skin->Init(L"Gimmick_Button.cmo", nullptr);
	m_Skin->SetPosition(m_Position);
	m_Skin->SetActive(true);
	m_PushSkin = NewGO<SkinModelRender>(0);
	m_PushSkin->Init(L"Press.cmo", nullptr);
	m_PushSkin->SetPosition(m_Position);
	m_PushSkin->SetActive(false);
	m_physicsOcject.CreateMeshObject(m_PushSkin->GetSkinModel(), m_Position, CQuaternion::Identity());
	return true;
}

void Gimmick_Button::Update()
{
	for (int i = 0; i < g_PlayerNum; i++) {
		CVector3 Diff = m_Player[i]->GetPosition() - m_Position;
		if (Diff.Length() < 40.0f) {
			if (!isOn) {
				if (m_Player[i]->GetPosition().y > m_Position.y + 10.0f&&
					m_Player[i]->GetPosition().y < m_Position.y + 50.0f) {
					m_PushSkin->SetActive(true);
					m_Skin->SetActive(false);
					isOn = true;
					m_Se.Play();
				}
			}
		}
	}
}
