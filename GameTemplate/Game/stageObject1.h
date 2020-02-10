#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
class Player;
class stageObject1 : public IGameObject
{
	//�h�b�X������ŁB
public:
	stageObject1();
	~stageObject1();
	bool Start();
	void Update();
	CVector3 GetTogePos() { //���W�̎擾�B
		return m_position;  //�����蔻��Ƃ��Ŏg���\��B
	}
private:

	Player* player[4] = {};
	int MaxPlayer;//�v���C���[�̍ő吔
	int PadNum;

	SkinModel m_model;  //�X�L�����f��

	CharacterController m_characon;

	CVector3 m_position = {0.0f,3200.0f,0.0f}; //���W�B

	CVector3 moveUpDown = CVector3::Zero();//�㉺�ɓ������B

	int timer = 0;     //����������ɂ�����Ǝ~�߂�B 

	void Draw();

	void Move();//��������

	bool UpDown = false;
};

