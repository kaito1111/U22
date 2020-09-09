#pragma once
#include "Player.h"

class CheckPoint : public IGameObject
{
public:
	CheckPoint();
	~CheckPoint();
	void SetPosition(CVector3 pos)
	{
		m_CheckPoint = pos;
	}
	void SetNum(int num) {
		PointNum = num;
	}
private:
	void SetPoint();
	CVector3 m_CheckPoint = CVector3::Zero();
	bool Start();
	void Update();
	GamePlayer* m_player[2];
	int PointNum = 0;
};

