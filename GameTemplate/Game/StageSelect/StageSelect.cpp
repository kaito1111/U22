#include "stdafx.h"
#include "StageSelect/StageSelect.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"StageSelect/TitleStage.h"
#include"StageSelect/TitleCamera.h"
#include"Stage.h"
#include<vector>
#include"Player.h"
#include "../CheckPointgenerator.h"
#include <iostream>
using namespace std;
StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
	DeleteGO(titleStage);
	DeleteGO(titleCamera);
}

bool StageSelect::Start()
{

	titleCamera = NewGO<TitleCamera>(1);
	titleStage = NewGO<TitleStage>(1);
	//player1 = FindGO<GamePlayer>("player1");
	//player2 = FindGO<GamePlayer>("player2");
	return true;
}

void StageSelect::Update()
{
	const CVector3 nextPlayer1Position = { 0.0f,200.0f,0.0f };
	const CVector3 nextPlayer2Position = { -50.0f,200.0f,0.0f };
	const int stageMax = 2;//�X�e�[�W�̐�.���
	const float stageXSize = -640.0f;//�I�ԃX�e�[�W�̉���
	//CVector3 pPos = player2->GetPosition();

	if (g_Pad->IsPress(enButtonA)) 
	{
		for (int nowStage = 0; nowStage < stageMax; nowStage++) {
			//�v���C���[1�̍��W����X�e�[�W��I�т܂�
			float a = stageXSize * (nowStage + 1);
			float b = stageXSize * nowStage;
			//if (pPos.x > a &&//�v���C���[�̍��W���X�v���C�g�E�[��菬����
			//	pPos.x < b) {//���[���傫���Ƃ�
			//	stage = NewGO<Stage>(1, "stage");
			//	stage->setStageNum(nowStage);
			//	//player1->SetPosition(nextPlayer1Position);
			//	//player2->SetPosition(nextPlayer2Position);
			//	DeleteGO(this);
			//}
		}
	}
	vector<float> stageLength;

}

void StageSelect::stageSelect()
{

	//const float moveSpeed = 100;	//�������x
	//const CVector3 scaleChangeSpeed = {0.5, 0.5, 0.5};   //�g�k���x
	//count++;

}