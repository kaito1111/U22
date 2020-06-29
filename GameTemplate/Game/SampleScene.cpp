#include "stdafx.h"
#include "SampleScene.h"
#include "Sample/DebugMan.h"
#include "SampleGround.h"

SampleScene::SampleScene()
{
	m_ground = NewGO<SampleGround>(0, "groundObj");
	m_debugMan = NewGO<DebugMan>(0, "debugManObj");
	auto cameraPos = g_camera3D.GetPosition();
}

SampleScene::~SampleScene()
{
}

void SampleScene::Update()
{

}