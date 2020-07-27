#include "stdafx.h"
#include "CheckPoint.h"

CheckPoint::CheckPoint() {

}

CheckPoint::~CheckPoint()
{
}

bool CheckPoint::Start()
{
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");
	return true;
}

void CheckPoint::Update()
{
	if (m_IsCurrent) {
		CVector3 diff = m_player[0]->GetPosition() - m_CheckPoint;
		if (diff.y <= 0.0) 
		{
			diff.y = -500;
		}
		float len = diff.Length();
		if (len >= 200.0f) {
			m_player[0]->SetCheckPoint(m_CheckPoint);
			m_point->SetCurrent(false);
		}
		diff = m_player[1]->GetPosition() - m_CheckPoint;
		len = diff.Length();
		if (len >= 200.0f) {
			m_player[1]->SetCheckPoint(m_CheckPoint);
			m_point->SetCurrent(false);
		}
	}
}
