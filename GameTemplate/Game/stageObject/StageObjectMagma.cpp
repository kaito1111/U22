#include "stdafx.h"
#include "StageObjectMagma.h"
#include"Player.h"

StageObjectMagma::StageObjectMagma(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/)
{
	//マグマになる予定なんだ。予定だけど。
	/*m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;*/
}


StageObjectMagma::~StageObjectMagma()
{
}

bool StageObjectMagma::Start()
{
	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
	m_pos.y -= 400.0f;
	m_model.Init(L"Assets/modelData/magma.cmo");
	return true;
}

void StageObjectMagma::Update()
{
	PlayerKill();
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
}

void StageObjectMagma::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void StageObjectMagma::PlayerKill()
{
	//プレイヤーキルとか書いてるけど、
	//動かす挙動もここにかくよ
	const float upSpeed = 0.2f;
	m_pos.y += upSpeed;

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 1.0f);
	m_rot.Multiply(qRot);

	CVector3 p1Pos = player1->GetPosition();
	CVector3 p2Pos = player2->GetPosition();
	const float YRange = m_pos.y + 200;
	if (p1Pos.y < YRange) {
		player1->MagumaDead();
	}
	if (p2Pos.y < YRange) {
		player2->MagumaDead();
	}
}