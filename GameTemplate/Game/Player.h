#pragma once
#include "character/CharacterController.h"
#include "graphics/2D/SpriteRender.h"

#include "Magnet/Magnet.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
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
	void Update();
	void Draw();
	SkinModel m_model;									//スキンモデル。
	SkinModel m_magnetModel;
	CharacterController m_characon;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_forward = CVector3::Front();

	MyMagnet::Magnet m_Magnet;
	int m_magnetSwich = 0;			//プレイヤーの磁力を切り替える変数

	int PadNo = 0;
	void SpawnPole();
	void Move();
	void MyMagnet();
};

