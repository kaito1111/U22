#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
#include "graphics/2D/SpriteRender.h"

class Player : public IGameObject , public Magnet
{
public:
	Player();
	CVector3 GetPosition() { 
		return m_position; 
	}
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	CVector3 GetForward() {
		return m_forward;
	}
	int GetMagnetNum() {
		return m_magnetSwich;
	}
	void SetPadNo(int No) {
		PadNo = No;
	}
private:
	~Player();
	void Update();
	void Draw();
	SkinModel m_model;									//�X�L�����f���B
	SkinModel m_magnetModel;
	CharacterController m_characon;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_forward = CVector3::Front();
	int m_magnetSwich = 0;			//�v���C���[�̎��͂�؂�ւ���ϐ�

	int PadNo = 0;
	void SpawnPole();
	void Move();
	void MyMagnet();
};

