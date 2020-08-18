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
	/// �p�b�h�̏�����
	/// </summary>
	/// <param name="pad">�p�b�h</param>
	void InitPad(PlayerPad* pad);
	void SIBOU();						
	void Press();						//���x���Ă�
	void MagumaDead();					//���x���Ă�
	void Cut();							//���x���Ă�

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

	SkinModel m_model;										//�X�L�����f���B
	SkinModel m_FrontModel;									//�X�L�����f���B
	SkinModel m_BuckModel;									//�X�L�����f���B
	CharacterController m_characon;
	CVector3 m_position = CVector3::Zero();
	CQuaternion	m_rot = CQuaternion::Identity();
	float m_rotAngle = 0.0f;
	enum Dir{//����
		L,//Left�@��
		R,//Right �E
		U,//Up    ��
		D,//Down  ��
		num
	};
	Dir dir = num;
	CVector3 m_forward = CVector3::Front();
	bool m_IsSi = false;
	CVector3 m_Scale	 = CVector3::One();
	bool m_PlayerCut	= false;
	CQuaternion	m_DefeatRot	 = CQuaternion::Identity();	//�|��Ă���Ƃ��̉�]��(�O��)
	CQuaternion	m_ReverseDefeatRot = CQuaternion::Identity(); //�|��Ă���Ƃ��̉�]��(�㑤)
	float rate = 0.0f;
	CVector3 m_CheckPoint = { 0.0f,0.0f,0.0f };		//���X�|�[���n�_

	float JumpTimer = 0.0f;
	SoundSource m_Se;					//�W�����v��
	SoundSource m_Se2;					//m_Se������Ă���Ƃ��ɗ����T�u����

	SpriteRender* m_ThisNumSprite = nullptr;
	int	m_PlayerNum = 0;
	SpriteRender* m_DieSprite = nullptr;

	MyMagnet::Magnet* m_Magnet = nullptr;
	bool HaveMagnet = false;
	CVector3 movespeed = CVector3::Zero();
//	ShadowMap* m_shadowMap = nullptr;				//�V���h�E�}�b�v

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

