#include "stdafx.h"
#include "MoveFloor2.h"


MoveFloor2::MoveFloor2()
{
}


MoveFloor2::~MoveFloor2()
{
}
void MoveFloor2::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool MoveFloor2::Start()
{

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/moveFloor2.cmo");
	//m_pos = { 0.0f,100.0f,0.0f };
	int MaxPlayer = Pad::CONNECT_PAD_MAX;
	StartPos = m_pos;

	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_Scale);
	return true;
}

void MoveFloor2::Update()
{
	//���b�V���̉]�X�B�v����ɓ����蔻��
	Move();
	m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);//�ÓI�����I�u�W�F�N�g
	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_Scale);
}

void MoveFloor2::Move()
{
	//�K�v�ɉ����ēK���ɂ������Ă�������
	const float speedUPLimit = 0;  //�X�s�[�h�̏��
	const float speedDownLimit = -7;//�X�s�[�h�̉���
	const float speed = 0.1;

	//���~�Ƃ������Ă邯�Ǎ��E�ɓ������c��ŁB
	//��
	if (UDPos == false) {

		//����
		if (speedDown == false) {
			moveSpeed += speed;
			//���l�܂ōs������������t���O��؂�ւ���
			if (moveSpeed >= speedUPLimit) {
				speedDown = true;
			}
		}

		//����
		if (speedDown == true) {
			moveSpeed -= speed;

			if (moveSpeed <= speedDownLimit) {
				speedDown = false;				//���l�܂ōs������t���O��؂�ւ���B
				UDPos = true;					//������؂��Ă���̂ŏ㏸���~�t���O���؂�ւ���
				moveSpeed = speedDownLimit;		//�X�s�[�h��0�ɍ��킹��
			}
		}
		m_pos.x += moveSpeed;
	}

	//�E
	if (UDPos == true) {

		//����
		if (speedDown == false) {
			moveSpeed += speed;
			//���l�܂ōs������t���O��؂�ւ���
			if (moveSpeed >= speedUPLimit) {
				speedDown = true;
			}
		}

		//����
		if (speedDown == true) {
			moveSpeed -= speed;
			//���l�܂ōs������t���O��؂�ւ���
			if (moveSpeed <= speedDownLimit) {
				speedDown = false;
				UDPos = false;
				moveSpeed = speedDownLimit;
			}
		}
		m_pos.x -= moveSpeed;
	}
}

void MoveFloor2::Move2()
{
	const float movespeed = 4;
	float y = m_pos.y;
	//�㏸
	if (y <= up && udlimit == false) {
		y += movespeed;
	}
	if (y >= up) {
		udlimit = true;
	}
	if (button->IsOn() == false) {
		//���~
		if (y >= down && udlimit == true) {
			y -= movespeed;
		}
		if (down >= y) {
			udlimit = false;
		}
		m_pos.y = y;
	}
	if (button->IsOn() == true) {
		m_pos = StartPos;
	}
}