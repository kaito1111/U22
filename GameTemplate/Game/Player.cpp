#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_characon.Init(20.0, 100.0f, m_position);
	//�v���C���[�Ɏ��͂���������
	LearnMO(&m_Magnet, m_position);
}


Player::~Player()
{
}

void Player::Update()
{
	MyMagnet();
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
	if (g_pad[PadNo].IsTrigger(enButtonRB1))
	{
		QueryGOs<NPole>("npole", [&](NPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		NPole* m_pole = NewGO<NPole>(1, "npole");
		CVector3 SpawnDir = { g_pad[PadNo].GetRStickXF() * -1.0f , g_pad[PadNo].GetRStickYF() , 0.0f };
		if (SpawnDir.Length() < 0.01f) {
			SpawnDir = m_forward;
		}
		CVector3 SpownPole = m_position;
		SpownPole.y = 50.0f;
		m_pole->SetPosition(SpownPole);
		m_pole->SetMoveDir(SpawnDir);
	}
	//SSpawn
	if (g_pad[PadNo].IsTrigger(enButtonLB1))
	{
		QueryGOs< SPole>("spole", [&](SPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		SPole* m_pole = NewGO< SPole>(1, "spole");
		CVector3 MoveDir = { g_pad[PadNo].GetRStickXF() * -1.0f , g_pad[PadNo].GetRStickYF() , 0.0f };
		if (MoveDir.Length() < 0.01f) {
			MoveDir = m_forward;
		}
		MoveDir.Normalize();
		m_pole->SetMoveDir(MoveDir);
		CVector3 SpownPole = m_position;
		SpownPole.y = 50.0f;
		m_pole->SetPosition(SpownPole);
	}
}

void Player::Move()
{
	//�W�����v����
	CVector3 movespeed = CVector3::Zero();
	if (m_Pad->IsTrigger(enButtonB) && m_characon.IsOnGround())
	{
		const float junpPower = 100.0f;
		movespeed.y = junpPower;
	}
	{
		//�d��
		const float gravity = 5.0f;
		movespeed.y -= gravity;
	}
	//���E�̈ړ�
	movespeed.x = m_Pad->GetLStickXF() * -20.0f;
	m_Magnet.MagnetMove();
	movespeed += m_Magnet.GetMove();
	m_position = m_characon.Execute(1.0f, movespeed);
	if (m_Pad->GetLStickXF() > 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	}
	if (m_Pad->GetLStickXF() < 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
}

void Player::MyMagnet()
{

	if (m_Pad->IsTrigger(enButtonY)) {
		m_magnetSwich++;
	}
	switch (m_magnetSwich)
	{
	case 0:
		m_Magnet.SetState(Magnet::State::NoMode);
		break;
	case 1:
		m_Magnet.SetState(Magnet::State::NMode);
		break;
	case 2:
		m_Magnet.SetState(Magnet::State::SMode);
		break;
	default:
		m_magnetSwich = 0;
		break;
	}
}
