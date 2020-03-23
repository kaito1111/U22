#include "stdafx.h"
#include "stageObjectShuriken.h"

//����m�F�Ƃ����邽�߂̃R���X�g���N�^�B�ŏI�����B
stageObjectShuriken::stageObjectShuriken()
{
	
}

//���x���z�u�p�̃R���X�g���N�^
//stageObjectShuriken::stageObjectShuriken(const wchar_t * modelName, CVector3 pos, CQuaternion rot)
//{
//}

stageObjectShuriken::~stageObjectShuriken()
{
}

bool stageObjectShuriken::Start()
{
	//���f���ǂ����悤���B
	m_model.Init(L"Assets/modelData/shuriken.cmo");

	return true;
}

void stageObjectShuriken::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void stageObjectShuriken::Update()
{
	//�����ɏ����Ă���̂ǂ����Ō������Ƃ���Ƃ������Ă͂����Ȃ��B
	const float speedUPLimit = 10;  //�X�s�[�h�̏��
	const float speedDownLimit = 0;//�X�s�[�h�̉���
	const float speed = 0.1;

	//migi
	if (UDPos == false) {

		//hidari
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
				UDPos = true;					//������؂��Ă���̂ō��E�t���O���؂�ւ���
				moveSpeed = speedDownLimit;		//�X�s�[�h��0�ɍ��킹��
			}
		}
		m_pos.x += moveSpeed;
	}

	//migi
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