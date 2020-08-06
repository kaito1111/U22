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
	//当たり判定作成
	physicsGround.CreateMeshObject(skin->GetSkinModel(), pos, qRot);
	return true;
}

void SampleGround::Update()
{
	auto m_shadowMap = g_graphicsEngine->GetShadowMap();
	//m_shadowMap->RegistShdowCaster(&skin->GetSkinModel());
}
