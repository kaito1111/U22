#include "stdafx.h"
#include "SampleScene.h"
#include "Sample/DebugMan.h"
#include "SampleGround.h"

SampleScene::SampleScene()
{
	//カメラの位置取得
	auto cameraPos = g_camera3D.GetPosition();
	//注視点設定
	g_camera3D.SetPosition({ 0,100.0f,200.0f });
	g_camera3D.SetTarget({0,0,0});
	g_camera3D.SetFar(5000.0f);
	g_camera3D.Update();
}

SampleScene::~SampleScene()
{
}

bool SampleScene::Start()
{
	//オブジェクトのインスタンス化
	m_ground = NewGO<SampleGround>(0, "groundObj");
	m_debugMan = NewGO<DebugMan>(0, "debugManObj");

	//ライトカメラの方向設定
	Engine().GetGraphicsEngine().GetShadowMap()->SetLightCameraRotation(CVector3{ 0.5f,-1.0f,0.0f });

	return true;
}

void SampleScene::Update()
{
	
}

void SampleScene::PostRender()
{
}