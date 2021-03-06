#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
	//m_SMagSprite = NewGO<myEngine::SpriteRender>(1);
	//m_SMagSprite->Init(L"Assets/sprite/MagnetBlue.dds", 50.0f, 50.0f, true);
	//m_SMagSprite->SetW(0.0f);
	////m_SMagSprite->SetPivot({ 1.0f,1.0f });
	//m_Rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	//m_SMagSprite->SetRotation(m_Rot);
	////m_SMagSprite->SetActive(false);
	//m_NMagSprite = NewGO<myEngine::SpriteRender>(1);
	//m_NMagSprite->Init(L"Assets/sprite/MagnetRed.dds", 50.0f, 50.0f, true);
	//m_NMagSprite->SetW(0.0f);
	////m_NMagSprite->SetPivot({ -1.0f,-1.0f });
	//m_NMagSprite->SetRotation(m_Rot);
	////m_NMagSprite->SetActive(false);
	m_Se.Init(L"Assets/sound/MagnetEffect3.wav");
	SEffect = NewGO<Effect>(1);
	NEffect = NewGO<Effect>(1);
}

Magnet::~Magnet()
{
}

CVector3 Magnet::MagnetMove()
{
	m_MagnetForce = CVector3::Zero();
	float MagnetPower = 0.025f;				//磁力の強さ
	float maganetLen = 300.0f;				//磁力が働く距離
	int MagnetNum = 0;						//磁石数
	QueryMO([&](Magnet* mag)->bool {
		//自分は計算しない
		if (mag == this) {
			return true;
		}
		CVector3 Diff = mag->GetPosition() - *m_Position;
		float len = Diff.Length();
		if (len < maganetLen &&
			!(mag->GetState() == NoMode)) {
			MagnetNum++;						//磁石をカウント
		}
		return true;
	});
	QueryMO([&](Magnet* mag)->bool {
		//自分は計算しない
		if (mag == this) {
			return true;
		}
		CVector3 diff = mag->GetPosition() - *m_Position;
		diff.z = 0.0f;
		float diffLen = diff.Length();
		float a = (maganetLen - diffLen);				//マグネットの力が遠いほど弱くなるやつ
		CVector3 MagnetForce = diff;					//磁力が働く方向
		MagnetForce.Normalize();
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:							//離れる
				if (diffLen < maganetLen) {				//磁力が働く距離内
					MagnetForce *= -(MagnetPower * a);
				}
				else {									//距離外
					MagnetForce = CVector3::Zero();
				}
				break;
			case Magnet::SMode:							//引き合う
				if (diffLen < maganetLen) {				//磁力が働く距離内
					MagnetForce *= (MagnetPower * a);
					if (mag->GetPosition().x < MagnetForce.x) {		//磁力で移動する距離よりターゲットのxが距離が近い
														//つまり余分に移動しようとしている
						MagnetForce.x = mag->GetPosition().x;			//移動するのはターゲットの距離まででいい
					}
					if (mag->GetPosition().z < MagnetForce.z) {		//磁力で移動する距離よりターゲットのzが距離が近い
														//つまり余分に移動しようとしている
						MagnetForce.z = mag->GetPosition().z;			//移動するのはターゲットの距離まででいい
					}
				}
				else {									//距離外
					MagnetForce = CVector3::Zero();
				}
				break;
			default:									//ターゲットが何属性でもない
				MagnetForce = CVector3::Zero();
				break;
			}
			break;
		case Magnet::SMode:
			switch (mag->GetState()) {
			case Magnet::NMode:							//引き合う
				if (diffLen < maganetLen) {				//磁力が働く距離内
					MagnetForce *= (MagnetPower * a);
					if (fabsf(mag->GetPosition().x) < MagnetForce.x) {		//磁力で移動する距離よりターゲットのxが距離が近い
														//つまり余分に移動しようとしている
						MagnetForce.x = mag->GetPosition().x;			//移動するのはターゲットの距離まででいい
					}
					if (fabsf(mag->GetPosition().z) < MagnetForce.z) {		//磁力で移動する距離よりターゲットのzが距離が近い
														//つまり余分に移動しようとしている
						MagnetForce.z = mag->GetPosition().z;			//移動するのはターゲットの距離まででいい
					}
				}
				else {									//距離外
					MagnetForce = CVector3::Zero();
				}
				break;
			case Magnet::SMode:							//離れる
				if (diffLen < maganetLen) {				//磁力が働く距離内
					MagnetForce *= -(MagnetPower * a);
				}
				else {									//距離外
					MagnetForce = CVector3::Zero();
				}
				break;
			default:									//ターゲットが何属性でもない
				MagnetForce = CVector3::Zero();
				break;
				return true;
			}
			break;
		case Magnet::NoMode:							//自分が何属性でもない
			MagnetForce = CVector3::Zero();
			break;
		default:										//自分が何属性でもない
			MagnetForce = CVector3::Zero();
			break;
		}
		MagnetForce.z = 0;								//zには動かなくていい
		if (mag->GetMove().y > 0.0f&&					//ターゲットが上に向かっているかつ
			MagnetForce.y > 0.0f						//自分も上に向かっているのはおかしいから
			) {
			MagnetForce.y = 0.0f;						//自分の移動を消す
		}
		m_MagnetForce += MagnetForce;					//最終的な移動量を足す
		if (m_MagnetForce.Length() >= 7.5) {
			MagnetForce.Normalize();
			MagnetForce *= 7.5f;
	}
		return true;
	});
	return m_MagnetForce;
}

void MyMagnet::Magnet::Update()
{
	switch (state)					//UI
	{
	case Magnet::SMode:
		SeVolume += 0.01f;
		if (SeVolume >= 1.0f) {
			SeVolume = 1.0f;
		}
		////m_SMagSprite->SetActive(true);
		//m_SMagSprite->SetW(1.0f);
		//m_NMagSprite->SetActive(false);
		////m_NMagSprite->SetW(0.0f);
		//if (m_Pad->IsTrigger(enButtonDown)) {
		//	SeVolume -= 0.1f;
		//}
		//if (m_Pad->IsTrigger(enButtonUp)) {
		//	SeVolume += 0.1f;
		//}
		if (NEffect->IsPlay() == false
			&& m_Se.IsPlaying() == false) {
			NEffect = NewGO<Effect>(1);
			NEffect->Play(L"Assets/effect/SMode.efk");
			NEffect->SetPosition(*m_Position);
			NEffect->SetScale(CVector3::One() * 2.75f);
			m_Se.Play();
		}
		break;
	case Magnet::NMode:
		SeVolume += 0.01f;
		if (SeVolume >= 1.0f) {
			SeVolume = 1.0f;
		}
		/*//m_SMagSprite->SetActive(false);
		m_SMagSprite->SetW(0.0f);
		//m_NMagSprite->SetActive(true);
		m_NMagSprite->SetW(1.0f);*/
		if (SEffect->IsPlay() == false
			&& m_Se.IsPlaying() == false) {
			SEffect = NewGO<Effect>(1);
			SEffect->Play(L"Assets/effect/NMode.efk");
			SEffect->SetPosition(*m_Position);
			SEffect->SetScale(CVector3::One() * 2.75f);
			m_Se.Play();
		}
		break;
	default:
		SeVolume -= 0.01f;
		if (SeVolume <= 0.0f) {
			SeVolume = 0.0f;
		}
		/*//m_SMagSprite->SetActive(false);
		m_SMagSprite->SetW(0.0f);
		//m_NMagSprite->SetActive(false);
		m_NMagSprite->SetW(0.0f);*/
		//CoolTime = 0;
		break;
	}
	if (NEffect != nullptr) {
		NEffect->SetPosition(*m_Position);
	}
	if (SEffect != nullptr) {
		SEffect->SetPosition(*m_Position);
	}
	//m_NMagSprite->SetPosition(*m_Position);
	//m_NMagSprite->Update();
	//m_Se.SetVolume(SeVolume);
	//m_SMagSprite->SetPosition({ m_Position->x,m_Position->y,m_Position->z });
	//m_SMagSprite->Update();
}

void MyMagnet::Magnet::PostRender()
{
	//m_NMagSprite->Draw();
	//m_SMagSprite->Draw();
}

bool MyMagnet::Magnet::Start()
{
	return true;
}
