/// <summary>
/// エフェクト再生のサンプルコード
/// </summary>

#include "stdafx.h"
#include "exEffect.h"
#include "Effect.h"

exEffect::exEffect()
{
	//再生&初期化
	effect->Play(L"Assets/effect/test.efk");
	effect->SetScale(CVector3::One() * 10);
}

exEffect::~exEffect()
{
	//DeleteGO(this);
}

void exEffect::Update()
{
	//デバッグ用のコード
	CVector3 ePos = m_pos;
	ePos = player->GetPosition();
	//ePos.y += 150;
	effect->SetPosition(ePos);
}
