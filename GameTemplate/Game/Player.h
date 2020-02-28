#pragma once
#include "character/CharacterController.h"
#include "graphics/2D/SpriteRender.h"

#include "Magnet/Magnet.h"
#include"HID/Pad.h"

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
	void SetPad(Pad* pad) {
		m_Pad = pad;
	}
	void Press();
private:
	bool Start();
	void Update();
	void Draw();

	SkinModel m_model;									//スキンモデル。
	CharacterController m_characon;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_forward = CVector3::Front();
	bool IsSi = false;
	CVector3 m_Scale = CVector3::One();

	MyMagnet::Magnet* m_Magnet = nullptr;
	int m_magnetSwich = 0;			//プレイヤーの磁力を切り替える変数

	Pad* m_Pad = nullptr;			//このプレイヤーのパッド
	void SpawnPole();
	void Move();
	void MyMagnet();
	void SIBOU();
};

