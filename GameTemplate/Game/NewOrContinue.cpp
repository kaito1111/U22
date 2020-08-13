#include "stdafx.h"
#include "NewOrContinue.h"
#include "KaitoTask.h"
#include"PlayerData.h"
#include "Stage.h"
#include"StageSelect/StageSelect.h"
#include<tuple>
#include"Game.h"
NewOrContinue::NewOrContinue()
{
}


NewOrContinue::~NewOrContinue()
{
	DeleteGO(m_spriteRender);
}

bool NewOrContinue::Start()
{
	
	m_spriteRender = NewGO<SpriteRender>(1, "sprite");
	m_spriteRender->Init(L"Assets/sprite/���߂���or��������.dds",1280,720);
	return true;
}

void NewOrContinue::Update()
{
	//int a = 0;
	//�ŏ�����i�X�e�[�W�Z���N�g��ʂցj�B
	if (g_Pad[0].IsPress(enButtonA)) {
		NewGO<StageSelect>(0, "stageSelect");
		DeleteGO(this);
	}
	//��������i�v���C���[�̍��W�ƃX�e�[�W�ԍ������[�h�j
	if (g_Pad[0].IsPress(enButtonX) && padB == true) {
		
		//�O��̃X�e�[�W�ƃv���C���[�̍��W�����[�h
		LoadPlayerData();
		game = NewGO<Game>(0, "game");
		Continue = true;
		game->setCon(Continue);
		game->setAll(player1(), player2(), GetStage());
		DeleteGO(this);
	}
	if (!g_Pad[0].IsTrigger(enButtonB)) {
		padB = true;
	}
}