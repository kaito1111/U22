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
	if (LBLobj()->GetPlayerNum() == 1) {
		//Update���Ԃ̒����̂��߂�NewGO�̃^�C�~���O�𒲐��B
		//�K��p1����Update�����悤�ɁB
		m_Player[0] = NewGO<GamePlayer>(1, "player1");
		m_Player[1] = NewGO<GamePlayer>(1, "player2");
		m_Player[0]->SetPlayerNum(1);
		m_Player[0]->SetPosition({ 100.0f, 0.0f, 0.0f });
		m_Player[1]->SetPlayerNum(2);
		m_Player[1]->SetPosition({ 200.0f, 0.0f, 0.0f });
	}
	else {
		//Update���Ԃ̒����̂��߂�NewGO�̃^�C�~���O�𒲐��B
		m_Player[1] = NewGO<GamePlayer>(1, "player2");
		m_Player[0] = NewGO<GamePlayer>(1, "player1");
		m_Player[1]->SetPlayerNum(1);
		m_Player[1]->SetPosition({ 200.0f, 0.0f, 0.0f });
		m_Player[0]->SetPlayerNum(2);
		m_Player[0]->SetPosition({ 100.0f, 0.0f, 0.0f });
	}
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
}

KaitoTask::~KaitoTask()
{
	DeleteGO(m_GameCamera);
	/*DeleteGO(m_Player[0]);
	DeleteGO(m_Player[1]);*/
}