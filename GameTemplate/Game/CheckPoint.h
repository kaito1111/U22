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
	bool m_IsCurrent = true;				//���̃`�F�b�N�|�C���g�ŕ������邩�ǂ���
											//�������鎞�ȂǂɎg�p����	
	CheckPoint* m_point = nullptr;
};

