#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
	m_SMagSprite = NewGO<myEngine::SpriteRender>(0);
	m_SMagSprite->Init(L"Assets/sprite/MagnetZero.dds", 200.0f, 100.0f);
	m_NMagSprite = NewGO<myEngine::SpriteRender>(0);
	m_NMagSprite->Init(L"Assets/sprite/MagnetZero.dds", 200.0f, 100.0f);
}

Magnet::~Magnet()
{
}

CVector3 Magnet::MagnetMove()
{
	m_Diff = CVector3::Zero();
	float MagnetPower = 2.0f;				//Ž¥—Í‚Ì‹­‚³
	float maganetLen = 50.0f;				//Ž¥—Í‚ª“­‚­‹——£
	QueryMO([&](Magnet* mag)->bool {
		if (mag == this) {
			return true;
		}
		CVector3 diff = CVector3::Zero();
		diff = mag->GetPosition() - *m_Position;
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				diff.z = 0;
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					*m_Position += diff * MagnetPower;
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					*m_Position -= diff * MagnetPower;
				}
				break;
			default:
				break;
			}
			break;
		case Magnet::SMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					*m_Position -= diff;
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					*m_Position += diff;
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
		m_Diff = diff;
		return true;
	});
	return *m_Position;
}