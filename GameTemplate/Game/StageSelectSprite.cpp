#include "stdafx.h"
#include "StageSelectSprite.h"
#include "Player.h"

StageSelectSprite::StageSelectSprite()
{
}

StageSelectSprite::~StageSelectSprite()
{
	DeleteGO(m_Stage1Sprite);
	DeleteGO(m_Stage2Sprite);
	DeleteGO(m_SelectSprite);
}

bool StageSelectSprite::Start()
{
	m_Stage1Sprite = NewGO<SpriteRender>(1);
	m_Stage1Sprite->Init(L"Assets/sprite/Corse1_image.dds", 150.0f, 150.0f, true);
	m_Stage1Sprite->SetPosition(m_Stage1SpritePos);

	m_Stage2Sprite = NewGO<SpriteRender>(1);
	m_Stage2Sprite->Init(L"Assets/sprite/Corse2_image.dds", 150.0f, 150.0f, true);
	m_Stage2Sprite->SetPosition(m_Stage2SpritePos);

	m_SelectSprite = NewGO<SpriteRender>(0);
	m_SelectSprite->Init(L"Assets/sprite/Yellow.dds", 170.0f, 170.0f, true);
	m_SelectSprite->SetW(0.0f);

	m_Player = FindGO<GamePlayer>("player");
	return true;
}

void StageSelectSprite::Update()
{
	//‹——£”äŠr‚µ‚Ä‘I‘ð‚µ‚Ä‚¢‚éŠG‚ðo‚·
	CVector3 diffXY1 = m_Player->GetPosition() - m_Stage1SpritePos;
	CVector3 diffXY2 = m_Player->GetPosition() - m_Stage2SpritePos;
	diffXY1.z = 0.0f;
	diffXY2.z = 0.0f;
	if (diffXY1.Length() < m_SelectLen) {
		m_SelectSprite->SetPosition(m_Stage1SpritePos);
		m_SelectSprite->SetW(1.0f);
	}
	else if (diffXY2.Length() < m_SelectLen) {
		m_SelectSprite->SetPosition(m_Stage2SpritePos);
		m_SelectSprite->SetW(1.0f);
	}
	else {
		m_SelectSprite->SetW(0.0f);
	}
}
