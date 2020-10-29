#include "stdafx.h"
#include "CheckPointgenerator.h"

CheckPointgenerator::CheckPointgenerator()
{
}

CheckPointgenerator::~CheckPointgenerator()
{
}

void CheckPointgenerator::OnDestroy()
{
	for (int i = 0; i < m_PointNum; i++) {
		DeleteGO(m_point[i]);
	}
}

void CheckPointgenerator::Load(wchar_t* filePass)
{
	if (m_filePass[0] == 0)
	{
		wcscpy(m_filePass, filePass);
		level.Init(m_filePass, [&](const auto& Object) {
			wchar_t CheckName[256] = {};
			swprintf(CheckName, L"CheckPoint%d", m_PointNum);
			if (wcscmp(Object.name, CheckName) == 0) {
				m_point[m_PointNum -1] = NewGO<CheckPoint>(0, "point");
				m_point[m_PointNum - 1]->SetPosition(Object.position);
				m_point[m_PointNum - 1]->SetNum(m_PointNum - 1);
				m_PointNum++;
			}
			return true;
		});
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
				m_point[PointNum - 1]->SetNum(PointNum - 1);
			}
			return true; 
		});
	}
	return true;
}
