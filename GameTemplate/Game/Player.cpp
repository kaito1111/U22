#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_characon.Init(100.0f, 20.0f, m_position);
}


Player::~Player()
{
}

void Player::Update()
{
	SpawnPole();
	Move();
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::SpawnPole()
{
	CMatrix mrot = CMatrix::Identity();
	mrot.MakeRotationFromQuaternion(m_rot);
	m_forward = { mrot.m[2][0],mrot.m[2][1],mrot.m[2][2] };
	m_forward.Normalize();
	//NSpawn
	if (g_pad->IsTrigger(enButtonRB1))
	{
		NPole* m_pole = NewGO<NPole>(1, "npole");
		m_pole->SetPosition(m_position);
		m_pole->SetForward(CVector3::Left()*-1.0f);
	}
	//SSpawn
	if (g_pad->IsTrigger(enButtonLB1))
	{
		SPole* m_pole = NewGO< SPole>(1, "spole");
		m_pole->SetPosition(m_position);
		m_pole->SetForward(CVector3::Left());
	}
}

void Player::Move()
{
	//�W�����v����
	CVector3 movespeed = CVector3::Zero();
	if (g_pad->IsTrigger(enButtonB))
	{
		movespeed.y = 100.0f;
	}
	movespeed.y -= 1.0f;

	//���E�̈ړ�
	movespeed.x = g_pad->GetLStickXF()*-1.0f;
	m_position = m_characon.Execute(1.0f, movespeed);
	if (g_pad->GetLStickXF() > 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	}
	if (g_pad->GetLStickXF() < 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
}
