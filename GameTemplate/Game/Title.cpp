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
	swprintf(m_text, L"マッチング中");
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
	//ルームの作成　そのルームが作成済みなら参加
	//キーボードのSpace g_Padの44行目参照
	if (g_Pad->IsTrigger(enButtonSelect)) {
	}


	if (INetworkLogic().GetLBL()->GetReady() &&
		!DeleteTitle ) {
		//ネットワークの準備が整った
		m_fade = NewGO<Fade>(0, "fade");
		DeleteTitle = true;
		swprintf(m_text, L"ゲームを開始します。");
	}
	if (GetAsyncKeyState('Y')) {
		NewGO<StageSelect>(0, "stageselect");
		DeleteGO(this);
	}
	//サンプルステージ
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
		//サンプル
		NetworkLogic::GetInstance().GetLBL()->RaiseGameScore(100, 200);
	}

	m_fontRender->SetTextUnsafe(m_text);
}

