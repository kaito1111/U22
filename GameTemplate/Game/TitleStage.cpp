#include "stdafx.h"
#include "TitleStage.h"


TitleStage::TitleStage()
{
}


TitleStage::~TitleStage()
{
}

bool TitleStage::Start()
{
	m_copymainRendrTarget.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//ステージのレベル配置前の情報
	skyModel.Init(L"Assets/modelData/sky.cmo");     //クソ雑魚背景
	m_model.Init(L"Assets/modelData/stage_00.cmo"); //ステージ1．
	m_model2.Init(L"Assets/modelData/stage3.cmo");	//ステージⅢ．おいおいⅢかよ
	return true;
}

void TitleStage::Update()
{
	
	skyModel.UpdateWorldMatrix({0,0,2000}, CQuaternion::Identity(), { 1,1,1 });
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_scale);
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);
	
}

void TitleStage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
	m_model2.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
	skyModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}

void TitleStage::PostRender()
{
	m_copymainRendrTarget.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copymainRendrTarget.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix());
}
