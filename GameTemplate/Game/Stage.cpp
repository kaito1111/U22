#include "stdafx.h"
#include "Stage.h"
#include "stageObjectJenerator.h"
#include"stageObject/Goal.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}

bool Stage::Start()
{
	//cmoファイルの読み込み。
	if (nowStage == 0) {
		m_model.Init(L"Assets/modelData/Course_Level1.cmo");
	}
	if (nowStage == 1) {
		m_model.Init(L"Assets/modelData/stage2.cmo");
	}
	if (nowStage == 2) {
		m_model.Init(L"Assets/modelData/stage3.cmo");
	}
	//シャドウレシーバーとする
	m_model.SetShadowReciever(true);
	m_phyStaticObuject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	generator = NewGO<stageObjectJenerator>(1, "generator");
	generator->setStageNum(nowStage);
	goal = FindGO<Goal>("Goal");
	return true;
}

void Stage::Update()
{		
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//g_graphicsEngine->GetShadowMap()->RegistShdowCaster(&m_model);
	//バレットフィジックスが出来次第チェックポイントのシステムを作る

	if (goal->IsClear() == true) {
		DeleteGO(this);
	}
}

void Stage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal,
		g_graphicsEngine->GetShadowMap()->GetLightViewMatirx(),
		g_graphicsEngine->GetShadowMap()->GetLightProjMatirx()
	);
}