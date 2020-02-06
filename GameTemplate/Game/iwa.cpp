#include "stdafx.h"
#include "Iwa.h"


Iwa::Iwa(const wchar_t* modelName, CVector3 pos, CQuaternion rot)
{
	m_model->Init(modelName);
	m_pos = pos;
	m_rot = rot;
}


Iwa::~Iwa()
{
}

void Iwa::Draw()
{
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Iwa::Update()
{

	m_model->UpdateWorldMatrix(m_pos, m_rot, {5.0f,5.0f,5.0f});
}
