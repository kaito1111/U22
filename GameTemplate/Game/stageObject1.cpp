#include "stdafx.h"
#include "stageObject1.h"
#include "Player.h"

stageObject1::stageObject1()
{
	//�h�b�X������ŁB

	//cmo�t�@�C���̓ǂݍ���
	m_model.Init(L"Assets/modelData/TogeToge.cmo");
	m_characon.Init(250.0f, 125.0f, m_position);
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
	float DownSpeed = -200.0f;	//�������x
	float UpSpeed = 77.0f;		//�㏸���x
	timer++;				//�����タ����Ǝ~�߂���

	//�㉺�^��
	if (m_position.y >= 1880
		&& timer >= 1200&&
		UpDown == false) {
		moveSpeed.y = DownSpeed;

		//�������������Ƃ�
		if (m_position.y <= 3400
			&&UpDown == false) {
			timer = 0;
			UpDown = true;
		}

	}
	if (m_position.y<=1880
		&&UpDown == true) {
		moveSpeed.y = UpSpeed;
		if (m_position.y >= 3400) {
			timer = 0;
			UpDown = false;
		}
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