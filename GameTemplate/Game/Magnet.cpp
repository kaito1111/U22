#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
}

Magnet::~Magnet()
{
}

CVector3 Magnet::MagnetTask()
{
	float maganetLen = 50.0f;				//Ž¥—Í‚ª“­‚­‹——£
	MagnetManeger().QueryObject([&](Magnet* mag)->bool
	{
		CVector3 diff;
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				diff = mag->GetPosition() - *m_Position;
				if (diff.Length() > maganetLen) {
					diff.Normalize();
					*m_Position -= diff;
				}
				break;
			case Magnet::SMode:
				diff = mag->GetPosition() + *m_Position;
				if (diff.Length() > maganetLen) {
					diff.Normalize();
					*m_Position += diff;
				}
				break;
			default:
				break;
			}
			break;
		case Magnet::SMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				diff = mag->GetPosition() + *m_Position;
				if (diff.Length() > maganetLen) {
					diff.Normalize();
					*m_Position += diff;
				}
				break;
			case Magnet::SMode:
				diff = mag->GetPosition() - *m_Position;
				if (diff.Length() > maganetLen) {
					diff.Normalize();
					*m_Position -= diff;
				}
				break;
			default:
				break;
				return true;
			}
		case Magnet::NoMode:
			break;
		default:
			break;
		}
	}
	);
	return *m_Position;
}
