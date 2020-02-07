#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"
class moveFloor : public IGameObject
{
public:
	//moveFloor(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
	moveFloor();
	~moveFloor();

	void Draw();
	void Update();
	void Move();
private:
	SkinModel m_model;					//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();				//���W
	CQuaternion m_rot = CQuaternion::Identity();	//��]
	bool UDPos= false;								//�オ��؂��Ă邩������؂��Ă邩
	bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
	float moveSpeed = 0;                            //���x�B�オ�����艺�������肷��
	bool sLimit = false;		    				//��������
	PhysicsStaticObject m_phyStaticObuject;         //�ÓI�����I�u�W�F�N�g
};

