#include "stdafx.h"
#include "iwa.h"
#include "level/Level.h"
#include "Player.h"

iwa::iwa()
{
	Level level;
	level.Init(L"Aseets/level.stage_iwa", nullptr);
	level.Draw();
	m_characon.Init(70.0f, 70.0f, m_position);
	player = FindGO<Player>("player");
}


iwa::~iwa()
{
}

void iwa::Update()
{

	m_model.UpdateWorldMatrix(m_position, m_Rot, CVector3::One());
}
