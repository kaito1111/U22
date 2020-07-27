#include "stdafx.h"
#include "KaitoTask.h"
#include "GameCamera.h"
#include "Player.h"

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
		m_Player[i] = NewGO<Player>(0, PlayerNo);
		m_Player[i]->SetPosition(SpownPos);
		m_Player[i++]->SetPlayerNum(i);
	}
	//NewGO<Goal>(1, "goal");
}

void KaitoTask::PreRender()
{
	auto shadowMap = g_graphicsEngine->GetShadowMap();
	//プレイヤー人数分シャドウキャスターとして登録
	for (int i = 0; i < g_PlayerNum;) {
		shadowMap->RegistShdowCaster(m_Player[i++]->GetModel());
	}
}

KaitoTask::~KaitoTask()
{
	//DeleteGO(m_GameCamera);
	DeleteGO(m_Player[0]);
	DeleteGO(m_Player[1]);
}