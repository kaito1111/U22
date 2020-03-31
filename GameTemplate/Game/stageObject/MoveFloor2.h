#pragma once
#include"physics/PhysicsStaticObject.h"
class MoveFloor2 : public IGameObject
{
//���E�ɓ������c��ŁB
public:
	MoveFloor2();
	~MoveFloor2();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}

private:
	void Draw();
	bool Start();
	void Update();
	void Move();
	
	SkinModel m_model;								//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();				//���W
	CQuaternion m_rot = CQuaternion::Identity();	//��]
	bool UDPos = false;								//�オ��؂��Ă邩������؂��Ă邩
	bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
	float moveSpeed = 0;                            //���x�B�オ�����艺�������肷��
	bool sLimit = false;		    				//��������
	PhysicsStaticObject m_phyStaticObject;          //�ÓI�����I�u�W�F�N�g
};

