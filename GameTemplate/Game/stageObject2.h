#pragma once
#include"character/CharacterController.h"
class Player;
class stageObject2: public IGameObject
{
	//�]�����Ă����
	//�傫���͔��a200�����̋��́A���ʂ͖���
	//visualStudio��200�ƋL������΂��傤�ǔ��a�Ɠ������������܂�
public:
	stageObject2();
	~stageObject2();
	bool Start();
	void Update();
	void Rorling();
	CVector3 GetMarutogePosition() {//���W�����
		return m_pos;
	};

	Player* player = nullptr;//�v���C���[�N���X
private:

	SkinModel* m_model = nullptr;			    //�X�L�����f��
	CVector3 m_pos = CVector3::Zero();          //���W
	CQuaternion m_rot = CQuaternion::Identity();//��]
	CVector3 scale = CVector3::One();			//�g��
	CharacterController charaCon;				//�L�����R��
	CVector3 moveSpeed = CVector3::Zero();		//�ړ����x
	void Draw();

};