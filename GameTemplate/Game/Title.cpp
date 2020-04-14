#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	m_Sprite = NewGO<SpriteRender>(1);
	m_Sprite->Init(L"Assets/sprite/Title.dds", 1280.0f, 720.0f,true);
}

Title::~Title()
{
	DeleteGO(m_Sprite);
}

void Title::Update()
{
	if (g_Pad->IsPress(enButtonA)) {
		NewGO<Game>(0, "game");
	}
}
