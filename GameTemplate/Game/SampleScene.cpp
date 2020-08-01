#include "stdafx.h"
#include "SampleScene.h"
#include "Sample/DebugMan.h"
#include "SampleGround.h"

SampleScene::SampleScene()
{
	//カメラの位置取得
	auto cameraPos = g_camera3D.GetPosition();
	//注視点設定
	g_camera3D.SetPosition(cameraPos);
	g_camera3D.SetTarget(Target);
	g_camera3D.SetFar(5000.0f);
	g_camera3D.Update();
}

SampleScene::~SampleScene()
{
}

bool SampleScene::Start()
{
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

	//オブジェクトのインスタンス化
	m_ground = NewGO<SampleGround>(0, "groundObj");
	m_debugMan = NewGO<DebugMan>(0, "debugManObj");

	//ライトカメラの方向設定
	g_graphicsEngine->GetShadowMap()->SetLightCameraRotation(CVector3{ 0.5f,-1.0f,0.0f });

	return true;
}

void SampleScene::Update()
{
	
}

void SampleScene::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}