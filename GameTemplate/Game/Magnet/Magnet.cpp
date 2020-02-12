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
	float MagnetPower = 10.0f;				//Ž¥—Í‚Ì‹­‚³
	float maganetLen = 50.0f;				//Ž¥—Í‚ª“­‚­‹——£
	QueryMO([&](Magnet* mag)->bool {

		//Ž©•ª‚ÍŒvŽZ‚µ‚È‚¢
		if (mag == this) {
			return true;
		}

		CVector3 diff = mag->GetPosition() - *m_Position;
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= MagnetPower;
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= MagnetPower;
				}
				break;
			default:
				diff = CVector3::Zero();
				break;
			}
			break;
		case Magnet::SMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= MagnetPower;
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= MagnetPower;
				}
				break;
			default:
				diff = CVector3::Zero();
				break;
				return true;
			}
		case Magnet::NoMode:
			diff = CVector3::Zero();
			break;
		default:
			break;
		}
		diff.z = 0;
		m_Diff = diff;
		return true;
	});
	return m_Diff;
}