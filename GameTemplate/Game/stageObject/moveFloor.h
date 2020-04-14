#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"
#include"Gimmick_Button.h"
class Player;
class moveFloor : public IGameObject
{
	//�T�C�Y200*200*20
public:
	moveFloor(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~moveFloor();

	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
	void SetMoveLimit(const float& limit) {
		up =  m_pos.y + limit;
		down =m_pos.y -  limit;
	}
private:
	bool Start();
	void Update();
	void Draw();
	void Move();

	Gimmick_Button* button = nullptr;
	SkinModel m_model;								//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();				//���W
	CQuaternion m_rot = CQuaternion::Identity();	//��]
	bool UDPos = false;								//�オ��؂��Ă邩������؂��Ă邩
	bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
	float moveSpeed = 0;                            //���x�B�オ�����艺�������肷��
	bool fastMove = false;                          //�ŏ��ɓ����Ƃ��̃t���O
	bool sLimit = false;		    				//��������
	PhysicsStaticObject m_phyStaticObject;          //�ÓI�����I�u�W�F�N�g
	SoundSource m_Se;
	CVector3 startPos = CVector3::Zero();

	void move2();
	float up = 0;
	float down = 0;
	bool start = false;
	bool udlimit = false;
	bool statPos = true;
};	

