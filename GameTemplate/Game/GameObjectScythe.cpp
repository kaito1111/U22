#include "stdafx.h"
#include "GameObjectScythe.h"


GameObjectScythe::GameObjectScythe()
{
}


GameObjectScythe::~GameObjectScythe()
{
}

bool GameObjectScythe::Start()
{
	m_pos.y += 490.0f;
	m_model.Init(L"Assets/modelData/Huriko.cmo");
	m_rot.SetRotationDeg(CVector3::AxisX(), -90.0f);
	return true;
}

void GameObjectScythe::Update()
{
	Move();
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
}

void GameObjectScythe::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void GameObjectScythe::Move()
{
	
	const float spinSpeedMin = 0.0f;//回転の最低速度
	const float spinSpeedMax = 50.0f;//回転の最大速度
	const float spinSpeedMinMax = -90.0f;//回転の最大速度
	const float speed = 1.0f;
	const float kariSpeed = 5.0f;//仮置きの速度
	//回転速度を伝えて振り子っぽく動かすよ.そのうちね！
	//Zのプラス方向に動かすプログラム
	spinSpeed += kariSpeed;
	if (spinSpeed >= 360) {
		spinSpeed = 0;
	}


	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), spinSpeed);
	m_rot = qRot;
	
}