#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "stageObjectJenerator.h"
Title::Title()
{
}


Title::~Title()
{
	
}

bool Title::Start()
{
	
	m_model.Init(L"Asset/modelData/stage_oreore.cmo");
	m_model2.Init(L"Asset/modelData/stageDossun.cmo");
	return true;
}

void Title::Update()
{
	stageSelect();
	
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_scale);
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);

	//nowStage���W�F�l���[�^�[�ɓn���āA���̐����ɉ�����NewGO������
	if (GetAsyncKeyState('K')) {
		NewGO<Game>(1);
		generator->setStageNum(nowStage);
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
	//�E�������ꂽ�Ƃ��ɍ�����ɂ���
	if(nowStage == 0					//�����̔ԍ��ȏ�
		||nowStage == -1				//�����̐������P������
		&&m_pos.x > LLimit				//�[�ɍs���Ă��邩�ǂ���
		&&RStageChange == true){		//�E�������ꂽ
		m_pos.x -= moveSpeed;			//������
			if (m_pos.x <= -LLimit) {
				m_pos.x = -LLimit;
				RStageChange = false;
			}
	}
	//���������ꂽ�Ƃ��ɉE����ɂ���
	if (nowStage >= 0					//�����̔ԍ��ȉ�
		|| nowStage == 1				//�����̐������1�傫��
		&& m_pos.x < RLimit			    //�[�ɍs���Ă��邩�ǂ���
		&& LStageChange == true) {		//���������ꂽ
		m_pos.x += moveSpeed;			//������
		if (m_pos.x <= -RLimit) {
			m_pos.x = -RLimit;
			LStageChange = false;
		}
	}
	//�����̔ԍ�����Ȃ��Ȃ����Ƃ��A����������

	if (nowStage != 0 && m_scale.x > 0) {
		m_scale.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 0 && m_scale.y > 0) {
		m_scale.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 0 && m_scale.z > 0) {
		m_scale.z -= scaleChangeSpeed.z;
	}
	////////////////////////////////////////////////////////////////////
	//�X�e�[�W2
	//�E�������ꂽ�Ƃ��ɍ�����ɂ���
	if (nowStage == 1					//�����̔ԍ��ȏ�
		|| nowStage == 0				//�����̐������P������
		&& m_pos2.x > LLimit			//�[�ɍs���Ă��邩�ǂ���
		&&RStageChange == true) {		//�E�������ꂽ
		m_pos2.x -= moveSpeed;			//������
		if (m_pos2.x <= -LLimit) {
			m_pos2.x = -LLimit;
			RStageChange = false;
		}
	}
	//���������ꂽ�Ƃ��ɉE����ɂ���
	if (nowStage >= 1					//�����̔ԍ��ȉ�
		|| nowStage == 2				//�����̐������1�傫��
		&& m_pos2.x < RLimit			//�[�ɍs���Ă��邩�ǂ���
		&& LStageChange == true) {		//���������ꂽ
		m_pos2.x += moveSpeed;			//������
		if (m_pos2.x <= -RLimit) {
			m_pos2.x = -RLimit;
			LStageChange = false;
		}
	}
	//�����̔ԍ�����Ȃ��Ȃ����Ƃ��A����������
	if (nowStage != 1 && m_scale2.x > 0) {
		m_scale2.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 1 && m_scale2.y > 0) {
		m_scale2.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 1 && m_scale2.z > 0) {
		m_scale2.z -= scaleChangeSpeed.z;
	}
}