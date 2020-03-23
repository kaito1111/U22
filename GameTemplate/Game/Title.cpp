#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"TitleStage.h"
Title::Title()
{
}


Title::~Title()
{
	DeleteGO(titleStage);
}

bool Title::Start()
{
	titleStage = NewGO<TitleStage>(1);
	return true;
}

void Title::Update()
{
	stageSelect();

	//nowStage���W�F�l���[�^�[�ɓn���āA���̐����ɉ�����NewGO������
	if (GetAsyncKeyState('K')) {
		NewGO<Game>(1);
		generator->setStageNum(nowStage);
		DeleteGO(this);
		
	}

}

void Title::stageSelect()
{
	const float LLimit = -2000;								//���[
	const float RLimit = 2000;								//�E�[
	const float moveSpeed = 100;							//�������x
	const CVector3 scaleChangeSpeed = {0.05, 0.05, 0.05};   //�g�k���x
	//�X�e�[�W�؂�ւ��̃t���O�ύX
	if (GetAsyncKeyState('D') && nowStage <stageMax) {
		RStageChange = true;
		nowStage++;
	}
	if (GetAsyncKeyState('A')&&nowStage > 0) {
		LStageChange = true;
		nowStage--;
	}
	////////////////////////////////////////////////////////////////
	//�X�e�[�W�P
	//stage1�̏��
	CVector3 pos1 = titleStage->GetPos();
	CVector3 scale1 = titleStage->GetScale();
	//�E�������ꂽ�Ƃ��ɍ�����ɂ���
	if(nowStage == 0					//�����̔ԍ��ȏ�
		||nowStage == -1				//�����̐������P������
		&& pos1.x > LLimit				//�[�ɍs���Ă��邩�ǂ���
		&&RStageChange == true){		//�E�������ꂽ
		pos1.x -= moveSpeed;			//������
			if (pos1.x <= -LLimit) {
				pos1.x = -LLimit;
				RStageChange = false;
			}
	}
	//���������ꂽ�Ƃ��ɉE����ɂ���
	if (nowStage >= 0					//�����̔ԍ��ȉ�
		|| nowStage == 1				//�����̐������1�傫��
		&& pos1.x < RLimit			    //�[�ɍs���Ă��邩�ǂ���
		&& LStageChange == true) {		//���������ꂽ
		pos1.x += moveSpeed;			//������
		if (pos1.x <= -RLimit) {
			pos1.x = -RLimit;
			LStageChange = false;
		}
	}
	//�����̔ԍ�����Ȃ��Ȃ����Ƃ��A����������
	

	if (nowStage != 0 && pos1.x > 0) {
		scale1.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 0 && pos1.y > 0) {
		scale1.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 0 && pos1.z > 0) {
		scale1.z -= scaleChangeSpeed.z;
	}
	////////////////////////////////////////////////////////////////////
	//�X�e�[�W2
	//stage2�̏��
	CVector3 pos2 = titleStage->GetPos2();
	CVector3 scale2 = titleStage->GetScale2();
	//�E�������ꂽ�Ƃ��ɍ�����ɂ���
	if (nowStage == 1					//�����̔ԍ��ȏ�
		|| nowStage == 0				//�����̐������P������
		&& pos2.x > LLimit			//�[�ɍs���Ă��邩�ǂ���
		&&RStageChange == true) {		//�E�������ꂽ
		pos2.x -= moveSpeed;			//������
		if (pos2.x <= -LLimit) {
			pos2.x = -LLimit;
			RStageChange = false;
		}
	}
	//���������ꂽ�Ƃ��ɉE����ɂ���
	if (nowStage >= 1					//�����̔ԍ��ȉ�
		|| nowStage == 2				//�����̐������1�傫��
		&& pos2.x < RLimit			//�[�ɍs���Ă��邩�ǂ���
		&& LStageChange == true) {		//���������ꂽ
		pos2.x += moveSpeed;			//������
		if (pos2.x <= -RLimit) {
			pos2.x = -RLimit;
			LStageChange = false;
		}
	}
	//�����̔ԍ�����Ȃ��Ȃ����Ƃ��A����������
	if (nowStage != 1 && scale2.x > 0) {
		scale2.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 1 && scale2.y > 0) {
		scale2.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 1 && scale2.z > 0) {
		scale2.z -= scaleChangeSpeed.z;
	}

	//�e�X�e�[�W�̏����X�V
	titleStage->SetPos(pos1);
	titleStage->SetPos(pos2);
	titleStage->SetScale(scale1);
	titleStage->SetScale(scale2);
}