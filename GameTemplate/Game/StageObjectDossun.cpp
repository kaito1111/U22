#include "stdafx.h"
#include "StageObjectDossun.h"
#include "Player.h"

StageObjectDossun::StageObjectDossun(const wchar_t* modelName, CVector3 pos, CQuaternion rot)
{
	m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;
}


StageObjectDossun::~StageObjectDossun()
{
}

bool StageObjectDossun::Start()
{
	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
	m_model.Init(L"Assets/modelData/Dossun.cmo");
	m_pos.y = 200.0f;
	startPos = m_pos;
	return true;
}

void StageObjectDossun::Update()
{
	Move();
	m_model.UpdateWorldMatrix(m_pos,m_rot,CVector3::One());
	staticObject.CreateMeshObject(m_model, m_pos, m_rot);
}

void StageObjectDossun::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void StageObjectDossun::Move()
{
	const float gatagataTimer = 4.0f;//揺らすときのがたつき。
	const float endGataGataDown = 4; //落下するまでのタイマー
	const float upSpeed = 1.8f;      //上昇速度
	const float DownSpeed = -18.0f; //下降速度
	//がたつきを作るための色々
	CQuaternion migi;
	migi.SetRotationDeg(CVector3::AxisZ(), 5.0f);
	CQuaternion hidari;
	hidari.SetRotationDeg(CVector3::AxisZ(), -5.0f);
	CQuaternion flont;
	flont.SetRotationDeg(CVector3::AxisZ(), 0.0f);

	count++;
	NextGataGata++;
	if (count >= gatagataTimer &&leftRight == false&&Up == true&& NextGataGata >= 30) {
		count = 0.0f;
		m_rot = migi;
		leftRight = true;
	}
	if (count >= gatagataTimer && leftRight == true&& Up == true) {
		count = 0.0f;
		m_rot = hidari;
		leftRight = false;
		yurashitaCount++;
		if (yurashitaCount >= 4) {
			yurashitaCount = 0;
			count = 0;
			Up = false;
			m_rot = flont;
		}
	}


	//オブジェクト150 200
	//プレイヤー20.50
	//170,250; 85 125  //42.5 125

	//プレイヤーのポジション
	CVector3 p1Pos = player1->GetPosition();
	CVector3 p2Pos = player2->GetPosition();

	//ｘとｙの範囲
	CVector3 toP1Pos = p1Pos - m_pos;
	toP1Pos.x = fabsf(toP1Pos.x);
	toP1Pos.y =	fabsf(toP1Pos.y);
	CVector3 toP2Pos = p2Pos - m_pos;
	toP2Pos.x = fabsf(toP2Pos.x);
	toP2Pos.y = fabsf(toP2Pos.y);
	const float xRange = 42.5f;
	const float yRange = 120.0f;
	if (Up == false && Down == false&&count >= 10) {
		if (oldPos.y < m_pos.y) {
			m_pos.y += DownSpeed;
			////////////////////////////////////////////
			//ココ当たり判定
			if (toP1Pos.x < xRange && toP1Pos.y < yRange) {
				player1->Press();
			}
			if (toP2Pos.x < xRange && toP2Pos.y < yRange) {
				player2->Press();
			}
			/////////////////////////////////////////////////
			if (oldPos.y >= m_pos.y) {
				Down = true;
				count = 0;
			}
		}	
	}
	if (Down == true&&count >= 100) {
		m_pos.y += upSpeed;
		if (m_pos.y >= startPos.y) {
			count = 0;
			NextGataGata = 0;
			m_pos = startPos;
			Down = false;
			Up = true;
		}
	}
}

void StageObjectDossun::playerKill()
{
}