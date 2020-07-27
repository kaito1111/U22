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
	void SetPoint(CheckPoint* point) {
		m_point = point;
	}
	void SetCurrent(bool current);
private:
	CVector3 m_CheckPoint = CVector3::Zero();
	bool Start();
	void Update();
	Player* m_player[2];
	bool m_IsCurrent = true;				//このチェックポイントで復活するかどうか
											//複数ある時などに使用する	
	CheckPoint* m_point = nullptr;
};

