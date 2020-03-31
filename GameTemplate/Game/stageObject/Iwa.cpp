#include "stdafx.h"
#include "Iwa.h"


Iwa::Iwa()
{
}


Iwa::~Iwa()
{
}

void Iwa::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Iwa::Update()
{
	//m_pos = MagnetMove();
	m_model.UpdateWorldMatrix(m_pos, m_rot, {5.0f,5.0f,5.0f});
}
