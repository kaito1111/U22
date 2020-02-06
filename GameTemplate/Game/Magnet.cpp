#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
	m_Sprite = NewGO<myEngine::SpriteRender>(0);
	m_Sprite->Init(L"Assets/sprite/MagnetZero.dds", 200.0f, 100.0f);

}

Magnet::~Magnet()
{
}

CVector3 Magnet::MagnetMove()
{
	float maganetLen = 50.0f;				//Ž¥—Í‚ª“­‚­‹——£
	QueryMO([&](Magnet* mag)->bool {
		CVector3 diff;
		switch (state)
		{
		case Magnet::NMode:
			m_Sprite->Init(L"Assets/sprite/MagnetBlue.dds", 200.0f, 100.0f);
			switch (mag->GetState()) {
			case Magnet::NMode:
				diff = mag->GetPosition() - *m_Position;
				if (diff.Length() > maganetLen) {
					diff.Normalize();
					*m_Position -= diff;
				}
				break;
			case Magnet::SMode:
				m_Sprite->Init(L"Assets/sprite/MagnetRed.dds", 200.0f, 100.0f);
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
		return true;
	});
	return *m_Position;
}