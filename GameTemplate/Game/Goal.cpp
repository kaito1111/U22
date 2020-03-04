#include "stdafx.h"
#include "Goal.h"
#include "Player.h"
#include "DirectionLight.h"

Goal::Goal()
{
	m_Skin.Init(L"Assets/modelData/Goal.cmo");
}

Goal::~Goal()
{
}

bool Goal::Start()
{
	m_player = FindGO<Player>("player1");
	return true;
}

void Goal::Update()
{
	float Len = 20.0f;				//ƒS[ƒ‹‚Ì”¼Œa
	CVector3 diff = m_player->GetPosition() - m_Position;
	float playerLen = diff.Length();
	if (playerLen < Len) {
		Effect* effect = NewGO<Effect>(1);
		if (!effect->IsPlay()) {
			effect->Play(L"Assets/effect/hemohage.efk");
			effect->SetPosition(m_Position);
			effect->SetScale(CVector3::One() * 20);
		}
	}
}
