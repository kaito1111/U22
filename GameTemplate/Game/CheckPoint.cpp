#include "stdafx.h"
#include "CheckPoint.h"

CheckPoint::CheckPoint() {
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::SetCurrent(bool current)
{
	m_IsCurrent = current;
	m_player[0]->SetCheckPoint(m_CheckPoint);
	m_player[1]->SetCheckPoint(m_CheckPoint);
}

bool CheckPoint::Start()
{
	return true;
}

void CheckPoint::Update()
{
	CVector3 diff = m_player[0]->GetPosition() - m_CheckPoint;		//プレイヤーとチェックポイントの
																	//ベクトルを取得
	if (diff.y <= 0.0)												//チェックポイントの下方向は無効
	{
		diff.y = -500;
	}
	float len = diff.Length();										//ベクトルを長さだけにする
	if (len >= 200.0f) {											//この範囲内なら
		m_IsCurrent = true;									//これを有効
	}
	diff = m_player[1]->GetPosition() - m_CheckPoint;	//上と同じ
	len = diff.Length();
	if (diff.y <= 0.0)
	{
		diff.y = -500;
	}
	if (len >= 200.0f) {
		if (m_point != nullptr) {
			m_point->SetCurrent(false);
		}
	}
	if (m_IsCurrent) {
		m_player[0]->SetCheckPoint(m_CheckPoint);
		m_player[1]->SetCheckPoint(m_CheckPoint);
	}
}
