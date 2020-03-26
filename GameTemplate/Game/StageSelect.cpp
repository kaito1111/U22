#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"TitleStage.h"
#include"TitleCamera.h"

StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
	DeleteGO(titleStage);
}

bool StageSelect::Start()
{

	titleCamera = NewGO<TitleCamera>(1);
	titleStage = NewGO<TitleStage>(1);
	return true;
}

void StageSelect::Update()
{
	stageSelect();

	//nowStage���W�F�l���[�^�[�ɓn���āA���̐����ɉ�����NewGO������
	if (GetAsyncKeyState('K')) {
		game = NewGO<Game>(0);
		generator = NewGO<stageObjectJenerator>(1);
		generator->setStageNum(nowStage);
		DeleteGO(this);
		
	}
	
}

void StageSelect::stageSelect()
{
	const int stageMax = 2;			//�X�e�[�W�̐�.���
	const float LLimit = 4000;		//���[
	const float RLimit = 0;			//�E�[
	const float moveSpeed = 100;	//�������x
	const CVector3 scaleChangeSpeed = {0.05, 0.05, 0.05};   //�g�k���x
	
	count++;
	if (GetAsyncKeyState('D') && nowStage <stageMax&&count >= 120) {//�X�e�[�W�؂�ւ��̃t���O�ύX
		RStageChange = true;
		nowStage++;
		count = 0;
	}
	if (GetAsyncKeyState('A')&&nowStage > 0 && count >= 120) {
		LStageChange = true;
		nowStage--;
		count = 0;
	}
	//�X�e�[�W�ԍ���0��菬�����Ȃ������A�O�ɂ���
	if (nowStage < 0) {
		nowStage = 0;
	}
	//�X�e�[�W�ԍ����ő�l���傫���Ȃ������A�ő�l��˂�����
	if (nowStage > stageMax) {
		nowStage = stageMax;
	}
	//�X�e�[�W�T
	CVector3 pos1 = titleStage->GetPos();
	CVector3 scale1 = titleStage->GetScale();
	if (nowStage == 0) {
		scale1 = CVector3::One();
	}
	if (nowStage != 0) {
		scale1 = CVector3::Zero();
	}
	//�X�e�[�W�U
	CVector3 pos2 = titleStage->GetPos2();
	CVector3 scale2 = titleStage->GetScale2();
	if (nowStage == 1) {
		scale2 = {1,1,1};
	}
	if (nowStage != 1) {
		scale2 = CVector3::Zero();
	}


	//�e�X�e�[�W�̏����X�V
	//�X�e�[�W�P
	titleStage->SetPos(pos1);
	titleStage->SetScale(scale1);
	//�X�e�[�W2
	titleStage->SetPos2(pos2);
	titleStage->SetScale2(scale2);
}