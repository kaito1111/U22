#pragma once
#include"physics/PhysicsStaticObject.h"
class StageObjectDossun : public IGameObject
{
public:
	StageObjectDossun();
	~StageObjectDossun();
	bool Start();
	void Update();
	void Draw();
	void Move();
private:
	SkinModel m_model;                          //�X�L�����f��
	CVector3 startPos = CVector3::Zero();		//�������W��ۑ�����
	CVector3 m_pos = CVector3::Zero();			//���W
	CVector3 oldPos = CVector3::Zero();         //�������ɐi��ł邩���邽�߂̍��W
	CQuaternion m_rot = CQuaternion::Identity();//��]��
	PhysicsStaticObject staticObject;			//�ÓI�����I�u�W�F�N�g
	bool Up = true;								//��ɂ��邩�̔���
	bool Down = false;	                        //���ɃC���J�̔���
	bool leftRight = false;						//���E�ɗh�炷���߂̃t���O
	int count = 0;                              //���Ԃ̃J�E���g
	int yurashitaCount = 0;                     //�h�炵���񐔂�ۑ�����ϐ�     
	int  NextGataGata = 0.0f;                   //�ēx�����o�����߂̃t���O

	
};

