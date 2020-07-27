#include "stdafx.h"
#include "StageSelect/TitleStage.h"


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
	
	static const float Haba = 640.0f;//画像の横幅



	return true;
}

void TitleStage::Update()
{
	
}
void TitleStage::Draw()
{
	//もう少しまともなステージ選択画面を作りたい
	//ワールド行列の更新
	/*m_floorModel.UpdateWorldMatrix(m_floorPos, CQuaternion::Identity(), CVector3::One());
	m_floorModel.Draw(
	g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
		);*/
}

void TitleStage::PostRender()
{
	m_copymainRendrTarget.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copymainRendrTarget.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix());
}


