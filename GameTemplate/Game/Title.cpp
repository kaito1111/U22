#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"
#include "Sample/SampleScene.h"
#include "Network/NetworkLogic.h"
#include "Network/LoadBalancingListener.h"
#include "StageSelect/StageSelect.h"

Title::Title()
{
	//NetworkLogic::GetInstance().Start();
	m_Sprite = NewGO<SpriteRender>(5);
	m_Sprite->Init(L"Assets/sprite/Title.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_bgm.Play("Title_bgm.wav");
	m_fontRender = NewGO<CFontRender>(0);
	m_fontRender->SetScale(1.0f);
	m_fontRender->SetPosition(m_fontPos);
	swprintf(m_text, L"�}�b�`���O��");
}

Title::~Title()
{
	//NetworkLogic::GetInstance().Disconnect();
	//NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	//printf("disconnect");
	DeleteGO(m_Sprite);
	DeleteGO(m_fontRender);
}

void Title::Update()
{
	//���[���̍쐬�@���̃��[�����쐬�ς݂Ȃ�Q��
	//�L�[�{�[�h��Space g_Pad��44�s�ڎQ��
	if (g_Pad->IsTrigger(enButtonSelect)) {
	}


	if (INetworkLogic().GetLBL()->GetReady() &&
		!DeleteTitle ) {
		//�l�b�g���[�N�̏�����������
		m_fade = NewGO<Fade>(0, "fade");
		DeleteTitle = true;
		swprintf(m_text, L"�Q�[�����J�n���܂��B");
	}
	if (GetAsyncKeyState('Y')) {
		NewGO<StageSelect>(0, "stageselect");
		DeleteGO(this);
	}
	//�T���v���X�e�[�W
	if (GetAsyncKeyState('H')) {
		NewGO<SampleScene>(0, "SampleScene");
		DeleteGO(this);
	}
	if (DeleteTitle) {
		if (m_fade->GetLengh() < 700.0f) {
			m_fontRender->SetColor({0.0f, 0.0f, 0.0f, 0.0f});
		}
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

	m_fontRender->SetTextUnsafe(m_text);
}

