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
				return false;
			}
			return true;
		});
		m_point[0]->SetCurrent(true);
		for (int i = 1; i < PointNum; i++) {
			m_point[i]->SetPoint(m_point[i - 1]);
		}
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
