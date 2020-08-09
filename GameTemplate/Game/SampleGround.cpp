#include "stdafx.h"
#include "SampleGround.h"

SampleGround::SampleGround()
{
}

SampleGround::~SampleGround()
{
}

bool SampleGround::Start()
{
	//モデル初期化
	skin = NewGO<SkinModelRender>(0);
	skin->Init(L"testGround.cmo");
	//シャドウレシーバーに設定
	skin->GetSkinModel().SetShadowReciever(true);

	//エフェクトのインスタンス
	m_effect1 = NewGO<Effect>(0);
	m_effect2 = NewGO<Effect>(0);

	//当たり判定作成
	physicsGround.CreateMeshObject(skin->GetSkinModel(), pos, qRot);
	return true;
}

void SampleGround::Update()
{
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();

	m_effect1->SetPosition({ 100, 10, 0 });
	m_effect1->SetScale(CVector3::One() * 10.0f);
	m_effect1->Play(L"Assets/effect/test.efk");
	m_effect2->SetPosition({ 200, 10, 0 });
	m_effect2->SetScale(CVector3::One() * 10.0f);
	m_effect2->Play(L"Assets/effect/test.efk");
	//m_shadowMap->RegistShdowCaster(&skin->GetSkinModel());
}
