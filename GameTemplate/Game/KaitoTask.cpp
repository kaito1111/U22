#include "stdafx.h"
#include "Player.h"
#include "KaitoTask.h"
#include "GameCamera.h"
#include "TwoP_Pad.h"
#include "PlayerPad.h"
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
		//�D��x���X�e�[�W��葁��
		m_Player[i] = NewGO<GamePlayer>(1, PlayerNo);
		m_Player[i]->SetPosition(SpownPos);
		m_Player[i++]->SetPlayerNum(i);
	}

	if (INetworkLogic().GetLBL()->GetPlayerNum() - 1 == 0) {
		//�v���C���[1
		m_Player[0]->SetPad(twoP_Pad().GetPPad());
		m_Player[1]->SetPad(twoP_Pad().GetNPad());
	}
	else {
		//�v���C���[2
		m_Player[0]->SetPad(twoP_Pad().GetNPad());
		m_Player[1]->SetPad(twoP_Pad().GetPPad());
	}


	//m_Player[0]->
}

void KaitoTask::PreRender()
{
	auto shadowMap = Engine().GetGraphicsEngine().GetShadowMap();
	//�v���C���[�l�����V���h�E�L���X�^�[�Ƃ��ēo�^
	for (int i = 0; i < g_PlayerNum;) {
		shadowMap->RegistShdowCaster(m_Player[i++]->GetModel());
	}
}

void KaitoTask::Update()
{
	twoP_Pad().Update();
}

KaitoTask::~KaitoTask()
{
	DeleteGO(m_GameCamera);
	DeleteGO(m_Player[0]);
	DeleteGO(m_Player[1]);
}