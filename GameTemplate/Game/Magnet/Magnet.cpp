#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
	m_SMagSprite = NewGO<myEngine::SpriteRender>(1);
	m_SMagSprite->Init(L"Assets/sprite/MagnetRed.dds", 50.0f, 50.0f, true);
	m_SMagSprite->SetW(0.0f);
	m_SMagSprite->SetPivot({ 1.0f,1.0f });
	m_Rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_SMagSprite->SetRotation(m_Rot);
	m_SMagSprite->SetActive(false);
	m_NMagSprite = NewGO<myEngine::SpriteRender>(1);
	m_NMagSprite->Init(L"Assets/sprite/MagnetBlue.dds", 50.0f, 50.0f, true);
	m_NMagSprite->SetW(0.0f);
	m_NMagSprite->SetPivot({ -1.0f,-1.0f });
	m_NMagSprite->SetRotation(m_Rot);
	m_NMagSprite->SetActive(false);
}

Magnet::~Magnet()
{
}

CVector3 Magnet::MagnetMove()
{
	m_MagnetForce = CVector3::Zero();
	float MagnetPower = 0.05f;				//磁力の強さ
	float maganetLen = 300.0f;				//磁力が働く距離
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
		diff.z = 0.0f;
		float diffLen = diff.Length();
		float a = 0;					//マグネットの力が遠いほど弱くなるやつ
		a =( maganetLen - diffLen);
		CVector3 MagnetForce = diff;
		MagnetForce.Normalize();
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				if (diffLen < maganetLen) {
					MagnetForce *= -(MagnetPower * a);
				}
				else {
					MagnetForce = CVector3::Zero();
				}
				break;
			case Magnet::SMode:
				if (diffLen < maganetLen) {
					MagnetForce *= (MagnetPower * a);
					if (diffLen < MagnetForce.Length()) {
						MagnetForce = diff;
					}
				}
				else {
					MagnetForce = CVector3::Zero();
				}
				break;
			default:
				MagnetForce = CVector3::Zero();
				break;
			}
			break;
		case Magnet::SMode:
			switch (mag->GetState()) {
			case Magnet::NMode:
				if (diffLen < maganetLen) {
					MagnetForce *= (MagnetPower * a);
					if (diffLen < MagnetForce.Length()) {
						MagnetForce = diff;
					}
				}
				else {
					MagnetForce = CVector3::Zero();
				}
				break;
			case Magnet::SMode:
				if (diffLen < maganetLen) {
					MagnetForce *= -(MagnetPower * a);
				}
				else {
					MagnetForce = CVector3::Zero();
				}
				break;
			default:
				MagnetForce = CVector3::Zero();
				break;
				return true;
			}
			break;
		case Magnet::NoMode:
			MagnetForce = CVector3::Zero();
			break;
		default:
			MagnetForce = CVector3::Zero();
			break;
		}
		MagnetForce.z = 0;
		MagnetForce /= MagnetNum;
		m_MagnetForce += MagnetForce;
		return true;
	});
	return m_MagnetForce;
}

void MyMagnet::Magnet::Update()
{
	switch (state)					//UI
	{
	case Magnet::SMode:
		m_SMagSprite->SetActive(true);
		m_SMagSprite->SetW(1.0f);
		m_NMagSprite->SetActive(false);
		m_NMagSprite->SetW(0.0f);
		break;
	case Magnet::NMode:
		m_SMagSprite->SetActive(false);
		m_SMagSprite->SetW(0.0f);
		m_NMagSprite->SetActive(true);
		m_NMagSprite->SetW(1.0f);
		break;
	default:
		m_SMagSprite->SetActive(false);
		m_SMagSprite->SetW(0.0f);
		m_NMagSprite->SetActive(false);
		m_NMagSprite->SetW(0.0f);
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

bool MyMagnet::Magnet::Start()
{
	return true;
}
