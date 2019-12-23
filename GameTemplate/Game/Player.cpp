#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_CharaCon.Init(100.0f, 20.0f, m_Position);
}


Player::~Player()
{
}

void Player::Update()
{
	CVector3 MoveSpeed = CVector3::Zero();
	if (g_pad->IsTrigger(enButtonB))
	{
		MoveSpeed.y = 100.0f;
	}
	MoveSpeed.y -= 1.0f;
	m_Position = m_CharaCon.Execute(1.0f, MoveSpeed);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_Position, CQuaternion::Identity(), CVector3::One());
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}