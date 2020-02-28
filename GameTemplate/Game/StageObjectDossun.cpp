#include "stdafx.h"
#include "StageObjectDossun.h"


StageObjectDossun::StageObjectDossun()
{
}


StageObjectDossun::~StageObjectDossun()
{
}

bool StageObjectDossun::Start()
{
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

	if (Up == false && Down == false&&count >= 10) {
		if (oldPos.y < m_pos.y) {
			m_pos.y += DownSpeed;
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
