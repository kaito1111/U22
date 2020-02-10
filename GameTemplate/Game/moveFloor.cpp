#include "stdafx.h"
#include "moveFloor.h"
#include "Player.h"

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
	//m_pos = { 50.0f,50.0f,0.0f };
	m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);

	player = FindGO<Player>("player");
	return true;
}

void moveFloor::Update()
{
	//���b�V���̉]�X�B�v����ɓ����蔻��
	

	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void moveFloor::Move()
{
	const float speedLimit = 100;//�X�s�[�h�̏��

	//�����ʒu�͏�B������v���O�����B
	if (UDPos == false && sLimit == false) {
		m_pos.y += -moveSpeed;	  //�����X�s�[�h���オ��
		moveSpeed++;
		if (moveSpeed >= speedLimit) {
			sLimit = true;		          //�X�s�[�h������܂ŗ�������ς���
		}
	}
	if (UDPos == false&& sLimit == true) {//���l�܂ŃX�s�[�h���オ���
		moveSpeed--;					  //�X�s�[�h�������Ă����B
		if (moveSpeed <= 0)				  //�X�s�[�h���O�ȉ��ɂȂ�����
			moveSpeed = 0;				  //�X�s�[�h�ɂO������B
			UDPos = true;				  //�����郂�[�h����オ�郂�[�h�ցB
			sLimit = false;				  //�X�s�[�h���~�b�g��߂��B
	}

	//�オ��v���O����
	if (UDPos == true && sLimit == false) {
		m_pos.y += moveSpeed;			  //�����X�s�[�h���オ��
		moveSpeed++;
		if (moveSpeed >= speedLimit) {
			sLimit = true;				  //���x���������Ԃɐ؂�ւ���t���O
		}
	}
	if (UDPos == true && sLimit == true) {//���l�܂ŃX�s�[�h���オ���
		moveSpeed--;                      //�X�s�[�h�������Ă����B
		if (moveSpeed <= 0)				  //�X�s�[�h���O�ȉ��ɂȂ�����
			moveSpeed = 0;				  //�X�s�[�h�ɂO������B
		UDPos = true;					  //�オ�郂�[�h���牺���郂�[�h�ցB
		sLimit = false;					  //���x��߂��B
	}	
}

void moveFloor::SetBoxDot()
{
	const float LengthAndWidth = 100.0f;//�c�Ɖ��̒���
	const float height =		 20.0f;//����

	///////�O////////////
	//�E��
	FrontRightUp.x += LengthAndWidth;
	FrontRightUp.z += LengthAndWidth;
	FrontRightUp.y += height;

	//�E��
	FrontRightDown.x += LengthAndWidth;
	FrontRightDown.z += LengthAndWidth;

	//����
	FrontLeftUp.x -= LengthAndWidth;
	FrontLeftUp.z += LengthAndWidth;
	FrontLeftUp.y += height;

	//����
	FrontLeftDown.x -= LengthAndWidth;
	FrontLeftDown.z += LengthAndWidth;


	/////���//////
	//�E��
	BackRightUp.x += LengthAndWidth;
	BackRightUp.z -= LengthAndWidth;
	BackRightUp.y += height;

	//�E��
	BackRightDown.x += LengthAndWidth;
	BackRightDown.z -= LengthAndWidth;

	//����
	BackLeftUp.x -= LengthAndWidth;
	BackLeftUp.z -= LengthAndWidth;
	BackLeftUp.y += height;

	//����
	BackLeftDown.x -= LengthAndWidth;
	BackLeftDown.z -= LengthAndWidth;


}

void moveFloor::CollisionDetection()
{

}
