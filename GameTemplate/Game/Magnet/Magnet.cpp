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
	float MagnetPower = 0.025f;				//���͂̋���
	float maganetLen = 300.0f;				//���͂���������
	int MagnetNum = 0;						//���ΐ�
	QueryMO([&](Magnet* mag)->bool {
		//�����͌v�Z���Ȃ�
		if (mag == this) {
			return true;
		}
		CVector3 Diff = mag->GetPosition() - *m_Position;
		float len = Diff.Length();
		if (len < maganetLen &&
			!(mag->GetState() == NoMode)) {
			MagnetNum++;						//���΂��J�E���g
		}
		return true;
	});
	QueryMO([&](Magnet* mag)->bool {
		//�����͌v�Z���Ȃ�
		if (mag == this) {
			return true;
		}
		CVector3 diff = mag->GetPosition() - *m_Position;
		diff.z = 0.0f;
		float diffLen = diff.Length();
		float a = (maganetLen - diffLen);				//�}�O�l�b�g�̗͂������قǎキ�Ȃ���
		CVector3 MagnetForce = diff;					//���͂���������
		MagnetForce.Normalize();
		switch (state)
		{
		case Magnet::NMode:
			switch (mag->GetState()) {
			case Magnet::NMode:							//�����
				if (diffLen < maganetLen) {				//���͂�����������
					MagnetForce *= -(MagnetPower * a);
				}
				else {									//�����O
					MagnetForce = CVector3::Zero();
				}
				break;
			case Magnet::SMode:							//��������
				if (diffLen < maganetLen) {				//���͂�����������
					MagnetForce *= (MagnetPower * a);
					if (mag->GetPosition().x < MagnetForce.x) {		//���͂ňړ����鋗�����^�[�Q�b�g��x���������߂�
														//�܂�]���Ɉړ����悤�Ƃ��Ă���
						MagnetForce.x = mag->GetPosition().x;			//�ړ�����̂̓^�[�Q�b�g�̋����܂łł���
					}
					if (mag->GetPosition().z < MagnetForce.z) {		//���͂ňړ����鋗�����^�[�Q�b�g��z���������߂�
														//�܂�]���Ɉړ����悤�Ƃ��Ă���
						MagnetForce.z = mag->GetPosition().z;			//�ړ�����̂̓^�[�Q�b�g�̋����܂łł���
					}
				}
				else {									//�����O
					MagnetForce = CVector3::Zero();
				}
				break;
			default:									//�^�[�Q�b�g���������ł��Ȃ�
				MagnetForce = CVector3::Zero();
				break;
			}
			break;
		case Magnet::SMode:
			switch (mag->GetState()) {
			case Magnet::NMode:							//��������
				if (diffLen < maganetLen) {				//���͂�����������
					MagnetForce *= (MagnetPower * a);
					if (fabsf(mag->GetPosition().x) < MagnetForce.x) {		//���͂ňړ����鋗�����^�[�Q�b�g��x���������߂�
														//�܂�]���Ɉړ����悤�Ƃ��Ă���
						MagnetForce.x = mag->GetPosition().x;			//�ړ�����̂̓^�[�Q�b�g�̋����܂łł���
					}
					if (fabsf(mag->GetPosition().z) < MagnetForce.z) {		//���͂ňړ����鋗�����^�[�Q�b�g��z���������߂�
														//�܂�]���Ɉړ����悤�Ƃ��Ă���
						MagnetForce.z = mag->GetPosition().z;			//�ړ�����̂̓^�[�Q�b�g�̋����܂łł���
					}
				}
				else {									//�����O
					MagnetForce = CVector3::Zero();
				}
				break;
			case Magnet::SMode:							//�����
				if (diffLen < maganetLen) {				//���͂�����������
					MagnetForce *= -(MagnetPower * a);
				}
				else {									//�����O
					MagnetForce = CVector3::Zero();
				}
				break;
			default:									//�^�[�Q�b�g���������ł��Ȃ�
				MagnetForce = CVector3::Zero();
				break;
				return true;
			}
			break;
		case Magnet::NoMode:							//�������������ł��Ȃ�
			MagnetForce = CVector3::Zero();
			break;
		default:										//�������������ł��Ȃ�
			MagnetForce = CVector3::Zero();
			break;
		}
		MagnetForce.z = 0;								//z�ɂ͓����Ȃ��Ă���
		if (mag->GetMove().y > 0.0f&&					//�^�[�Q�b�g����Ɍ������Ă��邩��
			MagnetForce.y > 0.0f						//��������Ɍ������Ă���̂͂�����������
			) {
			MagnetForce.y = 0.0f;						//�����̈ړ�������
		}
		m_MagnetForce += MagnetForce;					//�ŏI�I�Ȉړ��ʂ𑫂�
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
