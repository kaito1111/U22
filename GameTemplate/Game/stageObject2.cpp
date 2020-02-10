#include "stdafx.h"
#include "stageObject2.h"
#include"Player.h"

stageObject2::stageObject2()
{
	m_model->Init(L"Assets/modelData/RorlingRock.cmo");
	charaCon.Init(20.0, 100.0f, m_pos);
	m_pos.y += 200.0f;
}


stageObject2::~stageObject2()
{
}

bool stageObject2::Start()
{
	
	return true;
}

void stageObject2::Update()
{

	m_model->UpdateWorldMatrix(m_pos, m_rot, scale);
	m_pos = charaCon.Execute(1.0f, moveSpeed);
}

void stageObject2::Rorling()
{
	charaCon.SetPosition(m_pos);
	//‰ñ‚é‚º
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisZ(), 1.0f*0.3f);
	m_rot.Multiply(qRot);
}


void stageObject2::Draw()
{
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}