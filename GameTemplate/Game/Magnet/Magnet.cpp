#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
	m_SMagSprite = NewGO<myEngine::SpriteRender>(0);
	m_SMagSprite->Init(L"Assets/sprite/MagnetRed.dds", 200.0f, 100.0f);
	m_SMagSprite->SetW(0.0f);
	m_NMagSprite = NewGO<myEngine::SpriteRender>(0);
	m_NMagSprite->Init(L"Assets/sprite/MagnetBlue.dds", 200.0f, 100.0f);
	m_NMagSprite->SetW(0.0f);
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
					diff *= -MagnetPower;
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= MagnetPower;
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
					diff *= -MagnetPower;
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= MagnetPower;
				}
				break;
			default:
				break;
				return true;
			}
		case Magnet::NoMode:
			diff = CVector3::Zero();
			break;
		default:
			diff = CVector3::Zero();
			break;
		}
		diff.z = 0;
		m_Diff = diff;
		return true;
	});
	return m_Diff;
}

void MyMagnet::Magnet::Update()
{
	switch (state)
	{
	case Magnet::SMode:
		m_SMagSprite->SetW(1.0f);
		m_NMagSprite->SetW(0.0f);
		break;
	case Magnet::NMode:
		m_SMagSprite->SetW(0.0f);
		m_NMagSprite->SetW(1.0f);
		break;
	default:
		m_SMagSprite->SetW(0.0f);
		m_NMagSprite->SetW(0.0f);
		break;
	}
	m_NMagSprite->SetPosition(*m_Position);
	m_NMagSprite->Update(); 

	m_SMagSprite->SetPosition(*m_Position);
	m_SMagSprite->Update();

}

void MyMagnet::Magnet::PostDraw()
{
	m_NMagSprite->Draw();
	m_SMagSprite->Draw();
}