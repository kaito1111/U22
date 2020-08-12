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
	m_CharaCon.Init(50.0f, 100.0f, 1.0f, m_pos);
	return true;
}

void Iwa::Update()
{
	m_pos = m_magnet->MagnetMove();
	m_model->SetPosition(m_pos);
	m_model->SetRotation(m_rot);
	m_model->SetScale(CVector3::One());
}
