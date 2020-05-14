#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
#include "Network/NetworkLogic.h"
#include "Network/LoadBalancingListener.h"

Title::Title()
{
	NetworkLogic::GetInstance().Start();

	m_Sprite = NewGO<SpriteRender>(0);
	m_Sprite->Init(L"Assets/sprite/Title.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	); 
	m_bgm.Play("Title_bgm.wav");
}

Title::~Title()
{
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect");
	DeleteGO(m_Sprite);
}

void Title::Update()
{
	//�l�b�g�X�V�n����
	NetworkUpdate();

	g_camera2D.Update2D();
	g_camera3D.Update();
	if (g_Pad->IsPress(enButtonA)&&
		!DeleteTitle) {
		m_fade = NewGO<Fade>(0, "fade");
		DeleteTitle = true;
	}
	if (DeleteTitle) {
		if (m_fade->GetLengh() < 210.0f) {
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}
}

void Title::NetworkUpdate()
{
	//Network Test
	NetworkLogic::GetInstance().Update();
	if (g_Pad->IsTrigger(enButtonB)) {
		NetworkLogic::GetInstance().GetLBL()->RaiseGameScore(100, 200);
	}

	//���[���̍쐬�@���̃��[�����쐬�ς݂Ȃ�Q��
	//�L�[�{�[�h��Space g_Pad��44�s�ڎQ��
	if (g_Pad->IsTrigger(enButtonSelect)) {
		NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	}
}

void Title::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}