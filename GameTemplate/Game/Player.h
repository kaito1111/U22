#pragma once
#include "character/CharacterController.h"
#include "graphics/2D/SpriteRender.h"
#include "Magnet/Magnet.h"
#include "PlayerData.h"
class PlayerPad;

class GamePlayer : public PlayerData
{
public:
	GamePlayer();
	~GamePlayer();
	CVector3 GetPosition() { 
		return m_position; 
	}
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	CVector3 GetForward() {
		return m_forward;
	}
	void SetPoint(CVector3 point) {
		m_CheckPoint = point;
	}
	SkinModel* GetModel() {
		return &m_model;
	}

	/// <summary>
	/// パッドの初期化
	/// </summary>
	/// <param name="pad">パッド</param>
	void InitPad(PlayerPad* pad);
	void SIBOU();						
	void Press();						//何度も呼ぶ
	void MagumaDead();					//何度も呼ぶ
	void Cut();							//何度も呼ぶ

	void SetPlayerNum(int n)
	{
		m_PlayerNum = n;
	}

	int& GetPlayerNum()
	{
		return m_PlayerNum;
	}
	void ReSpown();
	void SetCheckPoint(CVector3 spownPoint);
private:
	bool Start();
	void Update();
	void Draw();

	SkinModel m_model;										//スキンモデル。
	SkinModel m_FrontModel;									//スキンモデル。
	SkinModel m_BuckModel;									//スキンモデル。
	CharacterController m_characon;
	CVector3 m_position = CVector3::Zero();
	CQuaternion	m_rot = CQuaternion::Identity();
	float m_rotAngle = 0.0f;
	enum Dir{//方向
		L,//Left　左
		R,//Right 右
		U,//Up    上
		D,//Down  下
		num
	};
	Dir dir = num;
	CVector3 m_forward = CVector3::Front();
	bool m_IsSi = false;
	CVector3 m_Scale	 = CVector3::One();
	bool m_PlayerCut	= false;
	CQuaternion	m_DefeatRot	 = CQuaternion::Identity();	//倒れているときの回転率(前側)
	CQuaternion	m_ReverseDefeatRot = CQuaternion::Identity(); //倒れているときの回転率(後側)
	float rate = 0.0f;
	CVector3 m_CheckPoint = { 0.0f,0.0f,0.0f };		//リスポーン地点

	float JumpTimer = 0.0f;
	SoundSource m_Se;					//ジャンプ音
	SoundSource m_Se2;					//m_Seが流れているときに流れるサブ音声

	SpriteRender* m_ThisNumSprite = nullptr;
	int	m_PlayerNum = 0;
	SpriteRender* m_DieSprite = nullptr;

	MyMagnet::Magnet* m_Magnet = nullptr;
	bool HaveMagnet = false;
	CVector3 movespeed = CVector3::Zero();
//	ShadowMap* m_shadowMap = nullptr;				//シャドウマップ

	enum enAniCli {
		Wait,
		Run,
		Junp,
		AnimaitionNum
	};
	AnimationClip m_AnimeClip[enAniCli::AnimaitionNum];
	Animation m_Animetion;
	void SpawnPole();
	void Move();
	void MyMagnet();
	SoundSource m_Asioto;

	PlayerPad* m_Pad = nullptr;
};

