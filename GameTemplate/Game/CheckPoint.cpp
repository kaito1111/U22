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
	CVector3 diff = m_player[0]->GetPosition() - m_CheckPoint;		//�v���C���[�ƃ`�F�b�N�|�C���g��
																	//�x�N�g�����擾
	if (diff.y <= 0.0)												//�`�F�b�N�|�C���g�̉������͖���
	{
		diff.y = -500;
	}
	float len = diff.Length();										//�x�N�g���𒷂������ɂ���
	if (len >= 200.0f) {											//���͈͓̔��Ȃ�
		m_IsCurrent = true;									//�����L��
	}
	diff = m_player[1]->GetPosition() - m_CheckPoint;	//��Ɠ���
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
