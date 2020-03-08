#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"

class Player;
class moveFloor : public IGameObject
{
	//�T�C�Y200*200*20
public:
	moveFloor(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
	~moveFloor();

	void Draw();
	bool Start();
	void Update();
	void Move();
private:
	SkinModel m_model;								//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();				//���W
	CQuaternion m_rot = CQuaternion::Identity();	//��]
	bool UDPos= false;								//�オ��؂��Ă邩������؂��Ă邩
	bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
	float moveSpeed = 0;                            //���x�B�オ�����艺�������肷��
	bool sLimit = false;		    				//��������
	PhysicsStaticObject m_phyStaticObject;          //�ÓI�����I�u�W�F�N�g

};	

