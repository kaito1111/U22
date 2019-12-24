#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"

class stageObject1 : public IGameObject
{
	//�h�b�X������ŁB
public:
	stageObject1();
	~stageObject1();
	void Update();

private:
	SkinModel m_model;  //�X�L�����f��

	CharacterController m_characon;

	CVector3 m_position = CVector3::Zero(); //���W�B

	CVector3 moveUpDown = CVector3::Zero();//�㉺�ɓ������B

	int timer = 0;     //����������ɂ�����Ǝ~�߂�B 

	void Draw();

	void Move();//��������

	bool UpDown = false;
};

