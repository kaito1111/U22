#include "stdafx.h"
#include "CheckPointgenerator.h"

CheckPointgenerator::CheckPointgenerator()
{
}

CheckPointgenerator::~CheckPointgenerator()
{
	for (auto p : m_point) {
		DeleteGO(p);
	}
}

void CheckPointgenerator::Load(wchar_t* filePass)
{
	if (m_filePass[0] == 0)
	{
		wcscpy(m_filePass, filePass);
		int PointNum = 0;
		level.Init(m_filePass, [&](const auto& Object) {
			wchar_t CheckName[256] = {};
			swprintf(CheckName, L"CheckPoint%d", ++PointNum);
			if (wcscmp(Object.name, CheckName) == 0) {
				m_point[PointNum -1] = NewGO<CheckPoint>(0, "point");
				m_point[PointNum - 1]->SetPosition(Object.position);
			}
			return true;
		});
		m_point[0]->SetCurrent(true);
		Player* m_p1 = FindGO<Player>("player1");
		m_p1->ReSpown();
		Player* m_p2 = FindGO<Player>("player2");
		m_p2->ReSpown();
	}
}

bool CheckPointgenerator::Start()
{
	if (m_filePass[0] == 0) {
		int PointNum = 0;
		level.Init(m_filePass, [&](const auto& Object)
		{
			wchar_t CheckName[256] = {};
			swprintf(CheckName, L"CheckPoint%d", ++PointNum);
			if (wcscmp(Object.name, CheckName) == 0) {
				m_point[PointNum - 1] = NewGO<CheckPoint>(0, "point");
				m_point[PointNum - 1]->SetPosition(Object.position);
				return false;
			}
			return true; 
		});
	}
	return true;
}
