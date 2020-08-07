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
	GamePlayer();//�R���X�g���N�^
	~GamePlayer();//�f�X�g���N�^
	CVector3 GetPosition() { //�ʒu��Ԃ�
		return m_position; 
	}
	void SetPosition(CVector3 pos, CVector3 moveSpeed = CVector3::Zero()) 
	/// <summary>
	/// �ʒu�����߂�
	/// </summary>
	/// <param name="pos">		�v���C���[�̈ړ��������</param>
	/// <param name="moveSpeed">�v���C���[�̈ړ��ʂ����߂�B
	///							���܂�g��Ȃ�</param>
	{
		m_characon.SetPosition(pos);
		if (moveSpeed.Length() > 1.0f) {
			m_position = m_characon.Execute(1.0f, moveSpeed);
		}
	}
	void SetPoint(CVector3 point) {//���X�|�[���ʒu��ݒ�
		m_CheckPoint = point;
	}
	SkinModel* GetModel() {//���f����Ԃ�
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
	void SetPad(IPad* pad);				//�R���g���[���[��ݒ肷��
	void SIBOU();						
	void Press();						//���x���Ă�
	void MagumaDead();					//���x���Ă�
	void Cut();							//���x���Ă�

	void SetPlayerNum(int n)//��P�����߂�
	{
		m_PlayerNum = n;
	}

	void ReSpown();//���X�|�[���n�_�ŕ�������
	
	void SetCheckPoint(CVector3 spownPoint)//���X�|�[���n�_�����߂�
	{
		m_CheckPoint = spownPoint;
	}
private:
	bool Start();//�����[��
	void Update();//���ՂŁ[��
	void Draw();//�ǂ�[
	int GetPadNo() const;//�R���g���[���[�̔ԍ���Ԃ�
	SkinModel m_model;										//�X�L�����f���B
	SkinModel m_FrontModel;									//�X�L�����f���B
	SkinModel m_BuckModel;									//�X�L�����f���B
	CharacterController m_characon;							//�L�����R��
	CVector3 m_position = CVector3::Zero();					//�ʒu
	CQuaternion	m_rot = CQuaternion::Identity();			//����
	float m_rotAngle = 0.0f;								//��]��
	enum Dir{//����
		L,//Left�@��
		R,//Right �E
		U,//Up    ��
		D,//Down  ��
		num
	};
	Dir dir = L;											//�����Ă����
	bool m_IsSi = false;									//���S���Ă��邩�ǂ���
	CVector3 m_Scale	 = CVector3::One();					//�傫��
	bool m_PlayerCut	= false;							//�؂�ꂽ���ǂ���
	CQuaternion	m_DefeatRot	 = CQuaternion::Identity();	//�|��Ă���Ƃ��̉�]��(�O��)
	CQuaternion	m_ReverseDefeatRot = CQuaternion::Identity(); //�|��Ă���Ƃ��̉�]��(�㑤)
	float rate = 0.0f;										//�؂�ꂽ�Ƃ��ɓ|���p�x
	CVector3 m_CheckPoint = { 0.0f,0.0f,0.0f };		//���X�|�[���n�_
	SoundSource m_Se;					//�W�����v��
	SoundSource m_Se2;					//m_Se������Ă���Ƃ��ɗ����T�u����

	SpriteRender* m_ThisNumSprite = nullptr;				//��P����\���G
	int	m_PlayerNum = 0;									//��P�H
	SpriteRender* m_DieSprite = nullptr;					//���񂾂�Ԃ��Ȃ�

	MyMagnet::Magnet* m_Magnet = nullptr;					//����
	bool HaveMagnet = false;								//���͂������Ă��邩�ǂ���
	CVector3 movespeed = CVector3::Zero();					//�ړ���
//	ShadowMap* m_shadowMap = nullptr;				//�V���h�E�}�b�v

	enum enAniCli {
		Wait,
		Run,
		Junp,
		AnimaitionNum
	};
	AnimationClip m_AnimeClip[enAniCli::AnimaitionNum];		//�A�j���[�V�������X�g
	Animation m_Animetion;									//�A�j���[�V����
	void SpawnPole();										//���ɂ��Ă�
	void Move();											//�ړ�����
	void MyMagnet();										//���ɂ�ύX����
	SoundSource m_Asioto;									//����

	IPad* m_Pad = nullptr;									//�p�b�h

	SpriteRender* m_SpriteN = nullptr;
	SpriteRender* m_SpriteS = nullptr;
	SpriteRender* m_SpriteJump = nullptr;
	SpriteRender* m_SpriteBase = nullptr;
	SpriteRender* m_SpriteDel = nullptr;
};