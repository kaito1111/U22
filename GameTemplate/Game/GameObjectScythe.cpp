#include "stdafx.h"
#include "GameObjectScythe.h"
#include"Player.h"

GameObjectScythe::GameObjectScythe()
{
}


GameObjectScythe::~GameObjectScythe()
{
}

bool GameObjectScythe::Start()
{
	//プレイヤーの検索
	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
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

void GameObjectScythe::PlayerKill()
{
	//40　400  -495.009
	const float hankei = 400.0f;
	const float haba = 40;
	const float hanteiPivotLen = -495.009;
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_rot);//これで回転行列が作られるらしい。
	m_front.Set(mRot.m[2][0], mRot.m[2][1], mRot.m[2][2]);//x = 0 , y = 1, z = 2。正面なのでｚと
	m_front.Normalize();

	m_right.Set(mRot.m[0][0], mRot.m[0][1], mRot.m[0][2]);
	m_right.Normalize();

	m_up.Set(mRot.m[1][0], mRot.m[1][1], mRot.m[1][2]);
	m_up.Normalize();

	CVector3 atariHantei = m_up * hanteiPivotLen;
	atariHantei.Dot(atariHantei);
	CVector3 toP1  = atariHantei - player1->GetPosition();
	CVector3 toP2 = atariHantei - player2->GetPosition();
	/*float toP1Lengh = toP1.Length();
	float toP2Lengh = toP2.Length();*/

	CVector3 pPos1 = player1->GetPosition();
	CVector3 pPos2 = player1->GetPosition();
	if (toP1.x < haba && toP1.y < hankei) {
		player1->Cut();
	}

	if (toP2.x < haba && toP2.y < hankei) {
		player2->Cut();
	}

	
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