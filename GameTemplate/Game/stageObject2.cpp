#include "stdafx.h"
#include "stageObject2.h"
#include"Player.h"

stageObject2::stageObject2()
{
	m_model->Init(L"Assets/modelData/maruToge.cmo");

}


stageObject2::~stageObject2()
{
}

bool stageObject2::Start()
{
	
	return true;
}

void stageObject2::Update()
{
	//距離図ってプレイヤーを殺す。演出とかも付けたいな。
	//出す場所も考えないと

	m_model->UpdateWorldMatrix(m_position, m_rotation, scale);
}


void stageObject2::Draw()
{
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}