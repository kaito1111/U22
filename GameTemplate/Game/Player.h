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
	void SetPad(Pad* pad) {
		m_Pad = pad;
	}
	void SetPoint(CVector3 point) {
		m_CheckPoint = point;
	}

	void SIBOU();						
	void Press();						//何度も呼ぶ
	void MagumaDead();					//何度も呼ぶ
	void Cut();							//何度も呼ぶ

	void SetPlayerNum(int n)
	{
		m_PlayerNum = n;
	}
	void UpDate();
private:
	bool Start();
	void Draw();

	SkinModel			m_model;										//スキンモデル。
	SkinModel			m_FrontModel;									//スキンモデル。
	SkinModel			m_BuckModel;									//スキンモデル。
	CharacterController m_characon;
	CVector3			m_position = CVector3::Zero();
	CQuaternion			m_rot = CQuaternion::Identity();
	CVector3			m_forward = CVector3::Front();
	bool				m_IsSi = false;
	CVector3			m_Scale	 = CVector3::One();
	bool				m_PlayerCut	= false;
	CQuaternion			m_DefeatRot	 = CQuaternion::Identity();	//倒れているときの回転率(前側)
	CQuaternion			m_ReverseDefeatRot = CQuaternion::Identity(); //倒れているときの回転率(後側)
	float				rate = 0.0f;
	CVector3			m_CheckPoint = { 0.0f,100.0f,0.0f };		//リスポーン地点

	float				JumpTimer = 0.0f;
	SoundSource m_Se;

	SpriteRender*		m_ThisNumSprite = nullptr;
	int					m_PlayerNum = 0;


	MyMagnet::Magnet*	m_Magnet = nullptr;
	CVector3			movespeed = CVector3::Zero();
	Pad*				m_Pad = nullptr;					//このプレイヤーのパッド

	void SpawnPole();
	void Move();
	void MyMagnet();
};

