#include "stdafx.h"
#include "CheckPoint.h"

CheckPoint::CheckPoint() {

}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::SetPoint()
{
	m_player[0]->SetCheckPoint(m_CheckPoint);
	m_player[1]->SetCheckPoint(m_CheckPoint);
}

bool CheckPoint::Start()
{
	m_player[0] = FindGO<GamePlayer>("player1");
	m_player[1] = FindGO<GamePlayer>("player2");
	if (PointNum == 0) {
		SetPoint();
	}
	m_player[0]->StartPos();
	m_player[1]->StartPos();
	return true;
}

void CheckPoint::Update()
{
	CVector3 diff = m_player[0]->GetPosition() - m_CheckPoint;
	if (diff.y <= 0.0)
	{
		diff.y = -500;
	}
	float len = diff.Length();
	if (len >= 200.0f) {
		m_player[0]->SetCheckPoint(m_CheckPoint);
	}
	diff = m_player[1]->GetPosition() - m_CheckPoint;
	len = diff.Length();
	if (len >= 200.0f) {
		m_player[1]->SetCheckPoint(m_CheckPoint);
	}
}
