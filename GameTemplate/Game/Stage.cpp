#include "stdafx.h"
#include "Stage.h"
#include "stageObjectJenerator.h"


Stage::Stage()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Course_Level1.cmo");
	//シャドウレシーバーとする
	m_model.SetShadowReciever(true);
	m_phyStaticObuject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	generator = NewGO<stageObjectJenerator>(1);

}


Stage::~Stage()
{

}

void Stage::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	//バレットフィジックスが出来次第チェックポイントのシステムを作る
}

void Stage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}