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
	//ルームの作成　そのルームが作成済みなら参加
	//キーボードのSpace g_Padの44行目参照
	if (g_Pad->IsTrigger(enButtonSelect)) {
	}

	g_camera2D.Update2D();
	g_camera3D.Update();
	if (INetworkLogic().GetLBL()->GetReady() &&
		!DeleteTitle ) {
		//ネットワークの準備が整った
		m_fade = NewGO<Fade>(0, "fade");
		DeleteTitle = true;
	}
	if (GetAsyncKeyState('Y')) {
		NewGO<StageSelect>(0, "stageselect");
		DeleteGO(this);
	}
	//サンプルステージ
	if (GetAsyncKeyState('H')) {
		NewGO<SampleScene>(0, "stageselect");
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
		//サンプル
		NetworkLogic::GetInstance().GetLBL()->RaiseGameScore(100, 200);
	}
}

void Title::NetworkUpdate()
{
	//Network Test
	//NetworkLogic::GetInstance().Update();

	//NetworkLogic::GetInstance().GetLBL()->RaiseInputPad(g_Pad->GetLStickXF(), g_Pad->GetLStickXF(), g_Pad->GetLStickXF(), g_Pad->GetLStickXF(), g_Pad->IsTrigger());
}
