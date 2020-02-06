#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"


Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_characon.Init(20.0, 100.0f, m_position);
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
	if (g_pad->IsTrigger(enButtonRB1))
	{
		QueryGOs<NPole>("npole", [&](NPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		NPole* m_pole = NewGO<NPole>(1, "npole");
		CVector3 SpawnDir = { g_pad->GetRStickXF() * -1.0f , g_pad->GetRStickYF() , 0.0f };
		if (SpawnDir.Length() < 0.01f) {
			SpawnDir = m_forward;
		}
		CVector3 SpownPole = m_position;
		SpownPole.y = 50.0f;
		m_pole->SetPosition(SpownPole);
		m_pole->SetMoveDir(SpawnDir);
	}
	//SSpawn
	if (g_pad->IsTrigger(enButtonLB1))
	{
		QueryGOs< SPole>("spole", [&](SPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		SPole* m_pole = NewGO< SPole>(1, "spole");
		CVector3 MoveDir = { g_pad->GetRStickXF() * -1.0f , g_pad->GetRStickYF() , 0.0f };
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
	//ジャンプ判定
	CVector3 movespeed = CVector3::Zero();
	if (g_pad->IsTrigger(enButtonB) && m_characon.IsOnGround())
	{
		movespeed.y = 100.0f;
	}
	movespeed.y -= 5.0f;

	//左右の移動
	movespeed.x = g_pad->GetLStickXF() * -20.0f;
	m_position = m_characon.Execute(1.0f, movespeed);
	if (g_pad->GetLStickXF() > 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	}
	if (g_pad->GetLStickXF() < 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
}

void Player::MyMagnet()
{

	if (g_pad->IsTrigger(enButtonY)) {
		m_magnetSwich++;
	}
	switch (m_magnetSwich)
	{
	case 0:
		SetState(State::SMode);
		break;
	case 1:
		SetState(State::NMode);
		break;
	case 2:
		SetState(State::NoMode);
		break;
	default:
		m_magnetSwich = 0;
		break;
	}
}
