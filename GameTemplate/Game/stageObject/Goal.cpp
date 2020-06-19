#include "stdafx.h"
#include "Goal.h"
#include "light/DirectionLight.h"

Goal::Goal(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/)
{
	/*m_Skin.Init(modelName);
	m_Position = pos;
	m_rot = rot;*/
}

Goal::~Goal()
{
}

bool Goal::Start()
{
	m_ClearSprite = NewGO<SpriteRender>(5);
	m_ClearSprite->Init(L"Assets/sprite/Clear.dds", 1420.0f, 720.0f);
	m_ClearSprite->SetW(0.0f);
	m_SkinRender = NewGO<SkinModelRender>(0);
	m_SkinRender->Init(L"Assets/modelData/Goal.cmo");
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");

	return true;
}

void Goal::Update()
{
	if (!isClear) {
		const float Len = 50.0f;				//ÉSÅ[ÉãÇÃîºåa
		const int clearNum = 2;
		int i;
		for (i = 0; i < clearNum;) {
			CVector3 diff = m_player[i]->GetPosition() - m_Position;
			float playerLen = diff.Length();
			if (playerLen < Len) {
				i++;
			}
			else {
				break;
			}
		}
		if (i == clearNum) {
			isClear = true;
			m_ClearSprite->SetW(1.0f);
			m_Se.Play();
		}
	}
	m_SkinRender->SetPosition(m_Position);
}
