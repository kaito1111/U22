#include "stdafx.h"
#include "ex2D.h"

namespace myEngine {
	ex2D::ex2D()
	{
		srv.CreateFromDDSTextureFromFile(L"Assets/modelData/a.dds");
		m_sprite.Init(srv, 500, 500);
	}


	ex2D::~ex2D()
	{
	}

	void ex2D::Update()
	{
		m_sprite.SetTextrue(srv);
		m_sprite.Update(m_position, m_rot, m_scale);
	}

	void ex2D::Draw()
	{
		m_sprite.Draw(rc, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}
