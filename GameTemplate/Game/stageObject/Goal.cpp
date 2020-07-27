#include "stdafx.h"
#include "Goal.h"
#include "light/DirectionLight.h"
#include "../Title.h"

Goal::Goal()
{
}

Goal::~Goal()
{
	DeleteGO(m_camera);
	DeleteGO(m_game);
	DeleteGO(m_ClearSprite);
}

bool Goal::Start()
{
	m_ClearSprite = NewGO<SpriteRender>(5);
	m_ClearSprite->Init(L"Assets/sprite/Clear.dds", 1420.0f, 720.0f);
	m_ClearSprite->SetW(0.0f);
	m_SkinRender = NewGO<SkinModelRender>(0);
	m_SkinRender->Init(L"Goal.cmo");
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");

	m_camera = FindGO<GameCamera>("camera");
	m_game = FindGO<Game>("game");
	return true;
}

void Goal::Update()
{
	if (!isClear) {
		const float Len = 50.0f;				//ゴールの半径
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
			m_camera->SetUpdate(false);
			CVector3 pos = m_Position;
			pos += {0.0f, 200.0f, 500.0f};
			g_camera3D.SetTarget({ m_Position.x,m_Position.y + 200.0f,m_Position.z });
			g_camera3D.SetPosition(pos);
			//カメラの更新。
			g_camera3D.Update();
			m_ClearSprite->SetW(1.0f);
		}
	}
	else {
		if (m_fade == nullptr) {
			if (g_Pad[0].IsPress(enButtonA)) {
				m_fade = NewGO<Fade>(6, "fade");
			}
		}
		else {
			float fadeLen = m_fade->GetLengh();
			if (m_fade->GetLengh() < 210.0f) {
				NewGO<Title>(0, "title");
				DeleteGO(this);
			}
		}

	}
	m_SkinRender->SetPosition(m_Position);
}
