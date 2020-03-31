#include "stdafx.h"
#include "stageObjectStopFloor.h"
#include "Player.h"
#include"Floor.h"


stageObjectStopFloor::stageObjectStopFloor(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/)
{
	/*m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;*/
}

stageObjectStopFloor::~stageObjectStopFloor()
{
	DeleteGO(floor);
}

bool stageObjectStopFloor::Start()
{
	floor = NewGO<Floor>(1);
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");
	m_model.Init(L"Assets/modelData/aStopFloor");//�ʂ�O�̃��f��
	return true;
}

void stageObjectStopFloor::Update()
{
	//�v���C���[�̃|�W�V�������擾
	playerPosition1 = m_player[0]->GetPosition();
	playerPosition2 = m_player[1]->GetPosition();

	//�v���C���[���������ɂ���Ƃ��A�t���O��false�ɂ���B
	if (playerPosition1.y < m_pos.y
		&& playerPosition2.y < m_pos.y) {
		upFlag = false;
	}
	//�����̍��W����ɍs������t���O�؂�ւ�
	if (playerPosition1.y > m_pos.y 
		|| playerPosition2.y > m_pos.y) {
		upFlag = true;
	}
	//�t���O�؂�ւ�������烂�f��NewGO�B�t���O��߂�
	if (upFlag == true&&NewGOModel == false) {
		floor = NewGO<Floor>(1);
		NewGOModel = true;
	}
	//�v���C���[���������ɍs�����Ƃ��A���f����j������
	if (upFlag == false && NewGOModel == true) {
		DeleteGO(floor);
		NewGOModel = false;
	}
}
