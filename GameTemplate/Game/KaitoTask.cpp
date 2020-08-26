#include "stdafx.h"
#include "Player.h"
#include "KaitoTask.h"
#include "GameCamera.h"
#include "TwoP_Pad.h"
#include "Network/NetworkLogic.h"

//#include "TitleStage.h"
//#include "TwoP_Pad.h"
//#include "stageObject/Goal.h"
//#include "stageObject/Gimmick_Button.h"

KaitoTask::KaitoTask()
{
	//NewGO<TitleStage>(5, "TitleStage");
	m_GameCamera = NewGO<GameCamera>(1, "camera");
	for (int i = 0; i < g_PlayerNum;) {
		CVector3 SpownPos = { 100.0f * i,0.0f,0.0f };
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", i + 1);
		//優先度をステージより早く
		m_Player[i] = NewGO<GamePlayer>(1, PlayerNo);
		m_Player[i++]->SetPosition(SpownPos);
	}
	if (LBLobj()->GetPlayerNum() == 1) {
		m_Player[0]->SetPlayerNum(1);
		m_Player[1]->SetPlayerNum(2);
	}
	else {
		m_Player[1]->SetPlayerNum(1);
		m_Player[0]->SetPlayerNum(2);
	}
}

void KaitoTask::PreRender()
{
	auto shadowMap = Engine().GetGraphicsEngine().GetShadowMap();
	//プレイヤー人数分シャドウキャスターとして登録
	for (int i = 0; i < g_PlayerNum;) {
		shadowMap->RegistShdowCaster(m_Player[i++]->GetModel());
	}
}

void KaitoTask::Update()
{
}

KaitoTask::~KaitoTask()
{
	DeleteGO(m_GameCamera);
	DeleteGO(m_Player[0]);
	DeleteGO(m_Player[1]);
}