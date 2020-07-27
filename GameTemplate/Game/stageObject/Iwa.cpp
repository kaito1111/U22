#include "stdafx.h"
#include "Iwa.h"


Iwa::Iwa()
{
	m_magnet = NewGO<Magnet>(1, "Magnet");
	LearnMO(m_magnet);
	m_magnet->SetPosition(&m_pos);
	m_model = NewGO<SkinModelRender>(5);
	m_model->Init(L"MagnetObject.cmo");
	m_CharaCon.Init(50.0f, 130.0f,1.0f, m_pos);
}


Iwa::~Iwa()
{
}

void Iwa::Update()
{
	m_pos += m_magnet->MagnetMove();
	m_model->SetPosition(m_pos);


	//m_pos = MagnetMove();
	//m_model->UpdateWorldMatrix(m_pos, m_rot, {5.0f,5.0f,5.0f});
}
