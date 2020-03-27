#include "stdafx.h"
#include "GameObjectScythe.h"
#include"Player.h"

//GameObjectScythe::GameObjectScythe(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/)
//{
//	/*m_model.Init(modelName);
//	m_pos = pos;
//	m_rot = rot;*/
//}


GameObjectScythe::GameObjectScythe()
{
}

GameObjectScythe::~GameObjectScythe()
{
}

bool GameObjectScythe::Start()
{
	//�v���C���[�̌���
	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
	m_pos.y += 490.0f;
	m_model.Init(L"Assets/modelData/Huriko.cmo");
	m_rot.SetRotationDeg(CVector3::AxisX(), -90.0f);
	
	return true;
}

void GameObjectScythe::Update()
{
	PlayerKill();
	Move();
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
}

void GameObjectScythe::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void GameObjectScythe::PlayerKill()
{
	//��]�s��
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rot);
	m_front.Set(mRot.m[2][0], mRot.m[2][1], mRot.m[2][2]);//x = 0 , y = 1, z = 2�B���ʂȂ̂ł���
	m_front.Normalize();

	m_right.Set(mRot.m[0][0], mRot.m[0][1], mRot.m[0][2]);
	m_right.Normalize();

	m_up.Set(mRot.m[1][0], mRot.m[1][1], mRot.m[1][2]);
	m_up.Normalize();


	const float hankei = 400.0f;//�������̔��a
	const float haba = 40;//�������̕�
	const float kamaNoChushin = -495.009;//���܂ł̒���
	
	//�v���C���[1
	CVector3 atariHantei = m_up * kamaNoChushin;
	atariHantei.Dot(atariHantei);
	CVector3 pPos1 = player1->GetPosition();//�v���C���[1�̃|�W�V����
	CVector3 toP1 = atariHantei - pPos1;//�v���C���[�P���犙�̋���
	//���Ƃ����Βl�ɕϊ�
	float atarihanteiHaba1 = 0;
	float atarihanteiTakasa1 = 0;
	/*float atarihanteiHaba1 = fabsf(toP1.x);
	float atarihanteiTakasa1 = fabsf(toP1.y);*/
	if (toP1.x < 0) {
		atarihanteiHaba1= toP1.x * -1;
	}
	if (toP1.y < 0) {
		atarihanteiTakasa1 =  toP1.y * -1;
	}
	if (atarihanteiHaba1 < haba && atarihanteiTakasa1 < hankei) {
		player1->Cut();
	}

	//�v���C���[�Q
	CVector3 atariHantei2 = m_up * kamaNoChushin;
	atariHantei2.Dot(atariHantei2);
	CVector3 pPos2 = player2->GetPosition();//�v���C���[�Q�̃|�W�V����
	CVector3 toP2 = atariHantei2 - pPos2;//�v���C���[�Q���犙�̋���
	//���Ƃ����Βl�ɕϊ�
	float atarihanteiHaba2 = 0;
	float atarihanteiTakasa2 = 0;
	if (toP2.x < 0) {
		atarihanteiHaba2 = toP2.x * -1;
	}
	if (toP2.y < 0) {
		atarihanteiTakasa2 = toP2.y * -1;
	}
	if (atarihanteiHaba2 < haba && atarihanteiTakasa2 < hankei) {
		player2->Cut();
	}
}

void GameObjectScythe::Move()
{
	
	const float spinSpeedMin = 0.0f;//��]�̍Œᑬ�x
	const float spinSpeedMax = 50.0f;//��]�̍ő呬�x
	const float spinSpeedMinMax = -90.0f;//��]�̍ő呬�x
	const float speed = 1.0f;
	const float kariSpeed = 5.0f;//���u���̑��x
	//��]���x��`���ĐU��q���ۂ���������.���̂����ˁI
	//Z�̃v���X�����ɓ������v���O����
	spinSpeed += kariSpeed;
	if (spinSpeed >= 360) {
		spinSpeed = 0;
	}


	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), spinSpeed);
	m_rot = qRot;
	
}