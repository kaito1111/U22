#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"
#include "Network/NetworkLogic.h"


TwoP_Pad::TwoP_Pad() {

	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++)
	{
		g_Pad[i].Init(i);
	}
	m_ManualSprite = NewGO<SpriteRender>(4);
	m_ManualSprite->Init(L"Assets/sprite/manual.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_ManualSprite->SetW(m_Manual_W);
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	m_ButtonSprite = NewGO<SpriteRender>(3);
	m_ButtonSprite->Init(L"Assets/sprite/Button.dds", 250.0f, 250.0f);
	CVector3 ButtonSpritePos = { 500.0f,-250.0f,0.0f };
	m_ButtonSprite->SetPosition(ButtonSpritePos);
}
TwoP_Pad::~TwoP_Pad()
{
	//for (int i = 0; i < g_PlayerNum;i++) {
	//	DeleteGO(player[i]);
	//}
	DeleteGO(m_ManualSprite);
}

void TwoP_Pad::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
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
	int PlayerPad = 0;
	g_Pad[PlayerPad].Update();

	

	//if (i < g_PlayerNum) {
	if (g_Pad[PlayerPad].IsTrigger(enButtonStart)
		//&&player[i]->GetUpdate()
		)
	{
		if (m_Manual_W == 0.0f)
		{
			m_Manual_W = 1.0f;
			m_ManualSprite->SetW(m_Manual_W);
			//player[i]->SetUpdate(false);
		}
		else
		{
			m_Manual_W = 0.0f;
			m_ManualSprite->SetW(m_Manual_W);
			//player[i]->SetUpdate(true);
		}
	}
	//}
	bool IsAllPad[EnButton::enButtonNum + 1] = {};
	IsAllPad[EnButton::enButtonNum] = 1;

	g_Pad[1].Update();
}
//}
