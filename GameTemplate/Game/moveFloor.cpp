#include "stdafx.h"
#include "moveFloor.h"
#include "Player.h"
#include"HID/Pad.h"
//moveFloor::moveFloor(const wchar_t * modelName, CVector3 pos, CQuaternion rot)
//{
//	m_model.Init(modelName);
//	m_pos = pos;
//	m_rot = rot;
//}
moveFloor::moveFloor()
{
	
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

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/moveFloor.cmo");
	m_pos = { 0.0f,100.0f,0.0f };
	//m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);//�ÓI�����I�u�W�F�N�g
	int MaxPlayer = Pad::CONNECT_PAD_MAX;
	/*for (int PadNum = 1; PadNum < MaxPlayer ; PadNum++) {
		char pl[256];
		sprintf(pl, "player%d", PadNum+1);

		player[PadNum] = FindGO<Player>(pl);
	}*/
	
	return true;
}

void moveFloor::Update()
{
	//���b�V���̉]�X�B�v����ɓ����蔻��
	Move();

	m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);//�ÓI�����I�u�W�F�N�g
	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void moveFloor::Move()
{
	const float speedUPLimit = 10;  //�X�s�[�h�̏��
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

void moveFloor::SetDotUpdate()
{

	////�������̃T�C�Y

	//const float LengthAndWidth = 100.0f;//�c�Ɖ��̒���
	//const float height =		 20.0f;//����
	//const float side =			 200.0f;//���̒���

	/////////�O////////////
	////�E��
	//FrontRightUp.x += side;
	//FrontRightUp.y += height;

	////�E��
	//FrontRightDown.x += side;

	////����
	//FrontLeftUp.x -= side;
	//FrontLeftUp.y += height;

	////����
	//FrontLeftDown.x -= side;


	////�v���C���[�̓����蔻��̃T�C�Y.10,100
	//const float PlayerYSize = 100.0f;
	//const float PlayerXSize = 10.0f;

	//if (PlayerNum >= 5) {
	//	PlayerNum = 1;
	//}
	//CVector3 PlayerPos = player[PlayerNum]->GetPosition();
	//PlayerRightUp = PlayerPos;
	//PlayerRightDown = PlayerPos;
	//PlayerLeftUp = PlayerPos;
	//PlayerLeftDown = PlayerPos;


	////�v���C���[�̉E��
	//PlayerRightUp.x += PlayerXSize;
	//PlayerRightUp.y += PlayerYSize;

	////�v���C���[�̉E��
	//PlayerRightDown.x += PlayerXSize;

	////�v���C���[�̍���
	//PlayerLeftUp.x -= PlayerXSize;
	//PlayerLeftUp.y += PlayerYSize;

	////�v���C���[�̍���
	//PlayerLeftDown.x -= PlayerXSize;


	//PlayerNum++;
}

void moveFloor::CollisionDetection()
{
	
}
