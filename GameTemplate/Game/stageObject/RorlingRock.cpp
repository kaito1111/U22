#include "stdafx.h"
#include "RorlingRock.h"
#include "Player.h"
RorlingRock::RorlingRock(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/)
{
	/*m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;*/
}

RorlingRock::~RorlingRock()
{
}

bool RorlingRock::Start()
{
	m_model.Init(L"Assets/modelData/RorlingRock.cmo");
	charaCon.Init(1.0f, 1.0f, m_pos);//キャラコンの初期化

	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
	return true;
}

void RorlingRock::Draw()
{
	//m_model.Draw(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix()
	//);
}

void RorlingRock::Update()
{
	killPlayer();
	Rorling();
	Move();
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
}

void RorlingRock::Rorling()
{

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisZ(), 1.0f*0.3f);
	m_rot.Multiply(qRot);
}

void RorlingRock::Move()
{
	moveSpeed.x -= 0.01f;
	moveSpeed.y--;
	m_pos = charaCon.Execute(1.0f, moveSpeed);

	m_pos.y += 200;

}

void RorlingRock::killPlayer()
{
	//当たり判定.それぞれのプレイヤーまでの距離
	CVector3 toP1 = player1->GetPosition() - m_pos;
	float toP1Length = toP1.Length();
	CVector3 toP2 = player2->GetPosition() - m_pos;
	float toP2Length = toP2.Length();
	
	if (toP1Length < 200.0f) {
		//ここに死亡処理書く。
		player1->MagumaDead();
	}
	if (toP2Length < 200.0f) {
		//ここに死亡処理書く。
		player2->MagumaDead();
	}
}
