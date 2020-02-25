#include "stdafx.h"
#include "RorlingRock.h"

RorlingRock::RorlingRock()
{
}

RorlingRock::~RorlingRock()
{
}

bool RorlingRock::Start()
{
	m_model.Init(L"Assets/modelData/RorlingRock.cmo");
	charaCon.Init(100.0f, 100.0f, m_pos);//キャラコンの初期化
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
