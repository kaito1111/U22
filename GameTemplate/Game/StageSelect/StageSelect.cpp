#include "stdafx.h"
#include "StageSelect/StageSelect.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"StageSelect/TitleStage.h"
#include"StageSelect/TitleCamera.h"
#include"Stage.h"
#include<vector>
#include"Player.h"
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
	player = FindGO<Player>("player1");
	return true;
}

void StageSelect::Update()
{
	const int stageMax = 2;//�X�e�[�W�̐�.���
	const float stageXSize = 640.0f;//�I�ԃX�e�[�W�̉���
	CVector3 pPos = player->GetPosition();
	if (g_Pad->IsPress(enButtonA)) {
		for (int nowStage = 0; nowStage < stageMax; nowStage++) {
			player = FindGO<Player>("player1");
			//�v���C���[1�̍��W����X�e�[�W��I�т܂�

			if (pPos.x < stageXSize * (nowStage + 1) &&//�v���C���[�̍��W���X�v���C�g�E�[��菬����
				pPos.x > stageXSize * (nowStage)) {    //���[���傫���Ƃ�

				stage = NewGO<Stage>(1, "stage");
				stage->setStageNum(nowStage);
				DeleteGO(this);
			}
		}

	}
	vector<float> stageLength;

}

void StageSelect::stageSelect()
{
	
	const float moveSpeed = 100;	//�������x
	const CVector3 scaleChangeSpeed = {0.5, 0.5, 0.5};   //�g�k���x
	count++;
	
}