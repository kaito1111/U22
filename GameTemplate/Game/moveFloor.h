#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"

class Player;
class moveFloor : public IGameObject
{
	//�T�C�Y200*200*20
public:
	//moveFloor(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
	moveFloor();
	~moveFloor();

	void Draw();
	bool Start();
	void Update();
	void Move();
	void SetBoxDot();         //�����̂̂S���_�̍��W
	void CollisionDetection();//�v���C���[�Ƃ̓����蔻��
private:
	Player* player[4] = {};
	int MaxPlayer;//�v���C���[�̍ő吔
	SkinModel m_model;								//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();				//���W
	CQuaternion m_rot = CQuaternion::Identity();	//��]
	bool UDPos= false;								//�オ��؂��Ă邩������؂��Ă邩
	bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
	float moveSpeed = 0;                            //���x�B�オ�����艺�������肷��
	bool sLimit = false;		    				//��������
	PhysicsStaticObject m_phyStaticObject;          //�ÓI�����I�u�W�F�N�g


	//�{�b�N�X�̐F�X

	//�O
	CVector3 FrontRightUp = CVector3::Zero();  //�E��
	CVector3 FrontRightDown = CVector3::Zero();//�E��
	CVector3 FrontLeftUp = CVector3::Zero();   //����
	CVector3 FrontLeftDown = CVector3::Zero(); //����

	//���
	CVector3 BackRightUp = CVector3::Zero();  //�E��
	CVector3 BackRightDown = CVector3::Zero();//�E��
	CVector3 BackLeftUp = CVector3::Zero();   //����
	CVector3 BackLeftDown = CVector3::Zero(); //����

};	

