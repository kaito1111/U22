#include "stdafx.h"
#include "Iwa.h"


Iwa::Iwa()
{
}


Iwa::~Iwa()
{
}

bool Iwa::Start()
{
	m_magnet = NewGO<Magnet>(1, "Magnet");
	LearnMO(m_magnet);
	m_magnet->SetPosition(&m_pos);
	m_model = NewGO<SkinModelRender>(5);
	m_model->Init(L"MagnetObject.cmo");
	m_CharaCon.Init(50.0f, 80.0f, 1.0f, m_pos);
	return true;
}

void Iwa::Update()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y -= 2.0f;
	m_moveSpeed += m_magnet->MagnetMove();
	m_pos = m_CharaCon.Execute(1.0f, m_moveSpeed);
	m_model->SetPosition(m_pos);
	m_model->SetRotation(m_rot);
	m_model->SetScale(CVector3::One());
}

void Iwa::OnDestroy()
{
	DeleteMO(m_magnet);
	DeleteGO(m_magnet);
	DeleteGO(m_model);
}
