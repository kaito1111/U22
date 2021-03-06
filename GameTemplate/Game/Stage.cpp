#include "stdafx.h"
#include "Stage.h"
#include "stageObjectJenerator.h"


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
		m_model.Init(L"Assets/modelData/stage3.cmo");
	}
	if (nowStage == 2) {
		m_model.Init(L"Assets/modelData/Course_Level2.cmo");
	}
	if (nowStage == 3) {
		m_model.Init(L"Assets/modelData/Course_Level1.cmo");
	}
	//シャドウレシーバーとする
	m_model.SetShadowReciever(true);
	m_phyStaticObuject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	generator = NewGO<stageObjectJenerator>(1, "generator");
	generator->setStageNum(nowStage);
	return true;
}

void Stage::Update()
{
	count++;
	if (count > 0 && newStage == false) {
		newStage = true;
		
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//g_graphicsEngine->GetShadowMap()->RegistShdowCaster(&m_model);
	//バレットフィジックスが出来次第チェックポイントのシステムを作る
}

void Stage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		enRenderMode_Normal,
		Engine().GetGraphicsEngine().GetShadowMap()->GetLightViewMatirx(),
		Engine().GetGraphicsEngine().GetShadowMap()->GetLightProjMatirx()
	);
}

void Stage::OnDestroy()
{
	DeleteGO(generator);
}
