#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"


Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_characon.Init(100.0f, 20.0f, m_position);
}


Player::~Player()
{
}

void Player::Update()
{
	CVector3 movespeed = CVector3::Zero();
	if (g_pad->IsTrigger(enButtonB))
	{
		movespeed.y = 100.0f;
	}
	movespeed.x = g_pad->GetLStickXF();

	movespeed.y -= 1.0f;
	m_position = m_characon.Execute(1.0f, movespeed);
	if (g_pad->GetLStickXF() < 0)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	}
	if (g_pad->GetLStickXF() > 0)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	}
	if (g_pad->IsTrigger(enButtonRB1))
	{
		NewGO< NPole>(1, "npole");
	}
	if (g_pad->IsTrigger(enButtonLB1))
	{
		NewGO< SPole>(1, "spole");
	}
	CMatrix mrot = CMatrix::Identity();
	mrot.MakeRotationFromQuaternion(m_rot);
	m_forward = { mrot.m[0][0],mrot.m[0][1],mrot.m[0][2] };
	m_forward.Normalize();
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rot, CVector3::One());
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}