#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
	m_SMagSprite = NewGO<myEngine::SpriteRender>(3);
	m_SMagSprite->Init(L"Assets/sprite/MagnetRed.dds", 200.0f, 100.0f, true);
	m_SMagSprite->SetActiveFlag(false);
	m_NMagSprite = NewGO<myEngine::SpriteRender>(3);
	m_NMagSprite->Init(L"Assets/sprite/MagnetBlue.dds", 200.0f, 100.0f, true);
	m_SMagSprite->SetActiveFlag(false);
}

Magnet::~Magnet()
{
}

CVector3 Magnet::MagnetMove()
{
	m_Diff = CVector3::Zero();
	float MagnetPower = 0.5f;				//磁力の強さ
	float maganetLen = 100.0f;				//磁力が働く距離
	int MagnetNum = 0;
	QueryMO([&](Magnet* mag)->bool {
		QueryMO([&](Magnet* mag)->bool {
			MagnetNum++; 
			return true;
		});

		//自分は計算しない
		if (mag == this) {
			return true;
		}

		CVector3 diff = mag->GetPosition() - *m_Position;
		/*if (mag->GetPosition().y != m_Position->y) {
			m_Position->y = mag->GetPosition().y;
			diff = mag->GetPosition() + *m_Position;
		}*/
		float a = 0;					//マグネットの力が遠いほど弱くなるやつ
		a = maganetLen - diff.Length();
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff*= -(MagnetPower * a);
				}
				else {
					diff = CVector3::Zero();
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= (MagnetPower * a);
				}
				else {
					diff = CVector3::Zero();
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
					diff *= (MagnetPower * a);
				}
				else {
					diff = CVector3::Zero();
				}
				break;
			case Magnet::SMode:
				if (diff.Length() < maganetLen) {
					diff.Normalize();
					diff *= -(MagnetPower * a);
				}
				else {
					diff = CVector3::Zero();
				}
				break;
			default:
				diff = CVector3::Zero();
				break;
				return true;
			}
			break;
		case Magnet::NoMode:
			diff = CVector3::Zero();
			break;
		default:
			diff = CVector3::Zero();
			break;
		}
		diff.z = 0;
		diff /= MagnetNum;
		m_Diff += diff;
		return true;
	}); 
	return m_Diff;
}

void MyMagnet::Magnet::Update()
{
	switch (state)
	{
	case Magnet::SMode:
		m_SMagSprite->SetActiveFlag(true);
		m_NMagSprite->SetActiveFlag(false);
		break;
	case Magnet::NMode:
		m_SMagSprite->SetActiveFlag(false);
		m_NMagSprite->SetActiveFlag(true);
		break;
	default:
		m_SMagSprite->SetActiveFlag(false);
		m_NMagSprite->SetActiveFlag(false);
		break;
	}
	m_NMagSprite->SetPosition(*m_Position);
	m_NMagSprite->Update(); 

	m_SMagSprite->SetPosition({ m_Position->x,m_Position->y,m_Position->z });
	m_SMagSprite->Update();
}

void MyMagnet::Magnet::PostDraw()
{
	m_NMagSprite->Draw();
	m_SMagSprite->Draw();
}