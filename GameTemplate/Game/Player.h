#pragma once
#include "character/CharacterController.h"
#include "graphics/2D/SpriteRender.h"
#include "Magnet/Magnet.h"
class PlayerPad;
class NetworkPad;
class IPad;

class GamePlayer : public IGameObject
{
public:
	GamePlayer();
	~GamePlayer();
	CVector3 GetPosition() { 
		return m_position; 
	}
	void SetPosition(CVector3 pos, CVector3 moveSpeed = CVector3::Zero()) {
		m_characon.SetPosition(pos);
		if (moveSpeed.Length() > 1.0f) {
			m_position = m_characon.Execute(1.0f, moveSpeed);
		}
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
	/// pad�̏�����
	/// <para>�|�����[�t�B�Y�����Ă��Ȃ�IPad�𑗂�Ȃ����ƁB</para>
	/// </summary>
	/// <remarks>
	/// ---pad�̏����ɂ���---
	/// 1.twoP_Pad��Pad�̎���(�Ή������^�Ƀ|�����[�t�B�Y��)�Ə����������āA
	/// 2.kaitoTask(�v���C���[�̃C���X�^���X�쐬��)�ŁA�ǂ�Pad���g���đ��삷�邩�̐ݒ�B
	/// ---exp---
	/// �|�����[�t�B�Y�����邱�ƂŊ֐�����ɏW��
	/// </remarks>
	/// <param name="pad">�|�����[�t�B�Y�����ꂽIPad</param>
	void SetPad(IPad* pad);
	void SIBOU();						
	void Press();						//���x���Ă�
	void MagumaDead();					//���x���Ă�
	void Cut();							//���x���Ă�

	void SetPlayerNum(int n)
	{
		m_PlayerNum = n;
	}
	void ReSpown();
	void SetCheckPoint(CVector3 spownPoint);
private:
	bool Start();
	void Update();
	void PreRender() override;
	void Draw();
	int GetPadNo() const;
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

	IPad* m_Pad = nullptr;
};

