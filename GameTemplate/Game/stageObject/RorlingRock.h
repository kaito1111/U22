#pragma once
#include"character/CharacterController.h"
class GamePlayer;
class RorlingRock : public IGameObject
{
public:
	RorlingRock(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~RorlingRock();
	bool Start();
	void Update();
	void Rorling();
	void Move();
	void killPlayer();
	void Draw();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
private:
	GamePlayer* player1 = nullptr;
	GamePlayer* player2 = nullptr;
	SkinModel m_model;//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();			//���W
	CVector3 m_scale = CVector3::One();			//�g�嗦
	CQuaternion m_rot = CQuaternion::Identity();//��]
	CharacterController charaCon;				//�L�����R��
	CVector3 moveSpeed = CVector3::One();		//�ړ����x

	//�v���C���[�̐l��
	Pad m_pad[Pad::CONNECT_PAD_MAX];//Pad�̐������ˁB
};

