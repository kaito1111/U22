#include "stdafx.h"
#include "Stage.h"



Stage::Stage()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/stage_00.cmo");
}


Stage::~Stage()
{

}

void Stage::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Stage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}