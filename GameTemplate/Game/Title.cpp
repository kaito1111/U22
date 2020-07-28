#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
#include "SampleScene.h"
#include "Network/NetworkLogic.h"
#include "Network/LoadBalancingListener.h"

Title::Title()
{
	//NetworkLogic::GetInstance().Start();
	printf("���[���ɓ���������́A�쐬���s���Ă��܂��B\n");
	NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	JString a[2];
	for (int i = 0; i < 2; i++) {
		a[i] = NetworkLogic::GetInstance().GetLBL()->GetUser(i);
	}

	printf("���[���ɓ��ꂵ�܂����B\n");
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
	//NetworkLogic::GetInstance().Disconnect();
	//NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	//printf("disconnect");
	DeleteGO(m_Sprite);
}

void Title::Update()
{
	//���[���̍쐬�@���̃��[�����쐬�ς݂Ȃ�Q��
	//�L�[�{�[�h��Space g_Pad��44�s�ڎQ��
	if (g_Pad->IsTrigger(enButtonSelect)) {
	}

	g_camera2D.Update2D();
	g_camera3D.Update();
	if (g_Pad->IsPress(enButtonA)&&
		!DeleteTitle) {
		m_fade = NewGO<Fade>(0, "fade");
		DeleteTitle = true;
	}
	//�T���v���X�e�[�W
	if (GetAsyncKeyState('Y')) {
		NewGO<SampleScene>(0, "ground");
		DeleteGO(this);
	}
	if (DeleteTitle) {
		if (m_fade->GetLengh() < 210.0f) {
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}

	//EventTest
	if (g_Pad->IsTrigger(enButtonB)) {
		//�T���v��
		NetworkLogic::GetInstance().GetLBL()->RaiseGameScore(100, 200);
	}
}

void Title::NetworkUpdate()
{
	//Network Test
	//NetworkLogic::GetInstance().Update();

	//NetworkLogic::GetInstance().GetLBL()->RaiseInputPad(g_Pad->GetLStickXF(), g_Pad->GetLStickXF(), g_Pad->GetLStickXF(), g_Pad->GetLStickXF(), g_Pad->IsTrigger());
}

void Title::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}