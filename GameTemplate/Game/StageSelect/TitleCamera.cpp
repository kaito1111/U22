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
	//カメラを初期化。
	g_camera3D.SetPosition(CVector3::One());
	g_camera3D.SetTarget(CVector3::Zero());
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	m_target = CVector3::Zero();
	static const float toTargetLen = 10000.0f; //カメラの注視点までの距離
	static const float texchaHigh = 240.0f;//テクスチャの高さの半分
	m_pos.z = toTargetLen;

	m_pos.y = texchaHigh;
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
	static const float width = 10000.0f;  //幅

	//左右のボタンでカメラの位置をずらします。
	//ステージの幅ずつずらしてます
	if (g_Pad[0].IsTrigger(enButtonRight) && nowChoiceStage < g_StageMAX-1)
	{
		nowChoiceStage++;
		m_pos.x -= width;
		m_target.x -= width;
	}
	if (g_Pad[0].IsTrigger(enButtonLeft) && nowChoiceStage > 0)
	{
		nowChoiceStage--;
		m_pos.x += width;
		m_target.x += width;
	}
}
