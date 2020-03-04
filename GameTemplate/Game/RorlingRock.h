#pragma once
#include"character/CharacterController.h"
class Player;
class RorlingRock : public IGameObject
{
public:
	RorlingRock();
	~RorlingRock();
	bool Start();
	void Update();
	void Rorling();
	void Move();
	void killPlayer();
	void Draw();
private:
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	SkinModel m_model;//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();			//���W
	CVector3 m_scale = CVector3::One();			//�g�嗦
	CQuaternion m_rot = CQuaternion::Identity();//��]
	CharacterController charaCon;				//�L�����R��
	CVector3 moveSpeed = CVector3::One();		//�ړ����x

	//�v���C���[�̐l��
	Pad m_pad[Pad::CONNECT_PAD_MAX];//Pad�̐������ˁB
};

