#pragma once
#include "level/Level.h"
#include "CheckPoint.h"
class CheckPointgenerator : public IGameObject
{
public:
	CheckPointgenerator();
	~CheckPointgenerator();

	void Load(wchar_t* filePass);
private:
	bool Start();
	void OnDestroy()override;
	CheckPoint* m_point[10] = {};
	Level level;
	wchar_t m_filePass[256] = {};
	int m_PointNum = 1;
};