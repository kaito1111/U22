#include "stdafx.h"
#include "StageSelect/TitleCamera.h"
#include "Player.h"
#include "StageSelect.h"
TitleCamera::TitleCamera()
{
	int a = 0;
}

TitleCamera::~TitleCamera()
{
	int a = 0;
}

bool TitleCamera::Start()
{
	m_target = CVector3::Zero();
	static const float toTargetLen = 100.0f; //カメラの注視点までの距離
	static const float texchaHigh = 240.0f;//テクスチャの高さの半分
	m_pos.z = toTargetLen;

	m_pos.y = texchaHigh;
	//カメラを初期化。
	g_camera3D.SetPosition(m_pos);
	g_camera3D.SetTarget(m_target);
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	//player = FindGO<Player>("player1");
	return true;
}

void TitleCamera::Update()
{
	Move();//移動関係

	//座標とかの更新
	g_camera3D.SetTarget(m_target); 
	g_camera3D.SetPosition(m_pos);
	g_camera3D.Update();
}

void TitleCamera::Move()
{
	float MoveSpeed = 5.0f;
	//左右のボタンでカメラの位置をずらします。
	//ステージの幅ずつずらしてます
	if (g_Pad[0].IsPress(enButtonRight))
	{
		m_target.x -= MoveSpeed;
	}
	if (g_Pad[0].IsPress(enButtonLeft))
	{
		m_target.x += MoveSpeed;
	}
	m_target.y = 100.0f;
	m_pos = m_target;
	m_pos.z += 500.0f;
}
