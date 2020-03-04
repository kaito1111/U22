#include "stdafx.h"
#include "RorlingRock.h"
#include "Player.h"
RorlingRock::RorlingRock()
{
}

RorlingRock::~RorlingRock()
{
}

bool RorlingRock::Start()
{
	m_model.Init(L"Assets/modelData/RorlingRock.cmo");
	charaCon.Init(100.0f, 100.0f, m_pos);//�L�����R���̏�����

	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
	return true;
}

void RorlingRock::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void RorlingRock::Update()
{
	Rorling();
	Move();
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

void RorlingRock::Rorling()
{

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisZ(), 1.0f*0.3f);
	m_rot.Multiply(qRot);
}

void RorlingRock::Move()
{
	moveSpeed.x -= 10.0f;
	moveSpeed.y--;
	m_pos = charaCon.Execute(1.0f, moveSpeed);

	m_pos.y += 200;

}

void RorlingRock::killPlayer()
{
	//�����蔻��.���ꂼ��̃v���C���[�܂ł̋���
	CVector3 toP1 = player1->GetPosition() - m_pos;
	float toP1Length = toP1.Length();
	CVector3 toP2 = player2->GetPosition() - m_pos;
	float toP2Length = toP2.Length();
	
	if (toP1Length < 200.0f|| toP2Length) {

	}
}
