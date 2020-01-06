#include "stdafx.h"
#include "ex2D.h"

namespace myEngine {
	ex2D::ex2D()
	{
		m_spriteRender = NewGO<SpriteRender>(1);
		m_spriteRender->Init(L"Assets/sprite/dummy.dds", 200, 200, false);
	}


	ex2D::~ex2D()
	{
	}

	void ex2D::Update()
	{
	}

	void ex2D::Draw()
	{
	}
}
