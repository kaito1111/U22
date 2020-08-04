#include "stdafx.h"
#include "moveFloor.h"
#include "Player.h"
#include"Gimmick_Button.h"
moveFloor::moveFloor(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/)
{
	/*m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;*/
	m_Se.Init(L"Assets/sound/moveFloor.wav");
	m_Se.SetVolume(0.5f);
}

moveFloor::~moveFloor()
{
}

void moveFloor::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool moveFloor::Start()
{
	m_player = FindGO<GamePlayer>("player1");
	m_player2 = FindGO<GamePlayer>("player2");
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/moveFloor.cmo");
	//m_pos = { 0.0f,100.0f,0.0f };
	int MaxPlayer = Pad::CONNECT_PAD_MAX;

	startPos = m_pos;
	//up = m_pos.y + 100;
	//down = m_pos.y - 100;
	m_BoxCharaCon.Init(100.0f, 20.0f, 1.0f, m_pos);//���I�u�W�F�N�g
	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	return true;
}

void moveFloor::Update()
{
	//���b�V���̉]�X�B�v����ɓ����蔻��
	//Move();
	move2();
	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void moveFloor::Move()
{
	//const float startUpLimit = 5;  //�ŏ��̃X�s�[�h�̏��
	const float speedUPLimit = 7;  //�X�s�[�h�̏��
	const float speedDownLimit = 0;//�X�s�[�h�̉���
	const float speed = 0.1;
	//���~
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
		m_pos.y += moveSpeed;
	}

	//�㏸
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
		m_pos.y -= moveSpeed;
	}
}

void moveFloor::move2()
{
	const float movespeed = 4;
	float y = m_pos.y;
	//�㏸
	if (y <= up && udlimit == false) {
		y += movespeed;
	}
	if (y >= up) {
		m_Se.Play(true);
		udlimit = true;
	}
	//���~
	if (y >= down && udlimit == true) {
		y -= movespeed;
	}
	if (down >= y) {
		m_Se.Play(true);
		udlimit = false;
	}
	CVector3 MoveSpeed = { 0.0f,y,0.0f };
	//m_pos.y = y;
	playerMove();
	m_pos = m_BoxCharaCon.Execute(1.0f, MoveSpeed);

}

void moveFloor::playerMove()
{
	CVector3 pl1pos = m_player->GetPosition();
	float diffY = m_pos.y - pl1pos.y;
	float diffX = m_pos.x - pl1pos.x;
	if (0.0f <= diffY <= 1.0f&&
		fabsf(diffX) <= m_BoxCharaCon.GetWide()) {
		m_player->SetPosition(pl1pos, { 0.0f,moveSpeed,0.0f });
	}
	CVector3 pl2pos = m_player2->GetPosition();
	diffY = m_pos.y - pl2pos.y;
	diffX = m_pos.x - pl2pos.x;
	if (0.0f <= diffY <= 1.0f&&
		fabsf(diffX) <= m_BoxCharaCon.GetWide()) {
		m_player2->SetPosition(pl2pos, { 0.0f,moveSpeed,0.0f });
	}
}