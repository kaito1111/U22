#include "stdafx.h"
#include "stageObject1.h"
#include "Player.h"

stageObject1::stageObject1()
{
	//�h�b�X������ŁB

	//cmo�t�@�C���̓ǂݍ���
	m_model.Init(L"Assets/modelData/TogeToge.cmo");
	m_characon.Init(1200.0f, 540.0f, m_position);
	m_position.y = 5000.0f;
}


stageObject1::~stageObject1()
{
	
}

void stageObject1::Update()
{
	Move();//�������z.

	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());

}



void stageObject1::Move()
{

	CVector3 moveSpeed = CVector3::Zero();//�ړ����x
	float Down = -200.0f;	//�������x
	float Up = 77.0f;		//�㏸���x
	timer++;				//�����タ����Ǝ~�߂���

	int a = 1;//�������̑���ɓ˂����ނ�B��ŏ����B

	if (a == 1/*������̎�*/
		&& timer >= 120) {
		moveSpeed.y = Down;
		if (a == 1/*�������������Ƃ�*/
			&& timer == 120) {
			timer = 0;
		}
	}
	if (a == 1/*����艺�ɍs�����Ƃ�*/) {
		moveSpeed.y = Up;
	}
	m_position = m_characon.Execute(1.0f, moveSpeed);
}


void stageObject1::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}