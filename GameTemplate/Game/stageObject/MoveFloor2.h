#pragma once
#include"physics/PhysicsStaticObject.h"
#include"Gimmick_Button.h"
#include "character/BoxCharactorController.h"
class MoveFloor2 : public IGameObject
{
//���E�ɓ������c��ŁB
public:
	MoveFloor2();
	~MoveFloor2();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
	CVector3 GetPosition() {
		return m_pos;
	}
	void SetMoveLimit(const float& limit) {
		up = m_pos.y + limit;
		down = m_pos.y - limit;
	}
	void SetScale(const CVector3& scale) {
		m_Scale = scale;
	}
private:
	Gimmick_Button* button = nullptr;
	void Draw();
	bool Start();
	void Update();
	void Move();
	void Move2();
	SkinModel m_model;								//�X�L�����f��
	CVector3 m_pos = CVector3::Zero();				//���W
	CQuaternion m_rot = CQuaternion::Identity();	//��]
	CVector3 m_Scale = CVector3::One();
	bool UDPos = false;								//�オ��؂��Ă邩������؂��Ă邩
	bool speedDown = false;							//�X�s�[�h���グ���艺�����肷��
	float moveSpeed = 0;                            //���x�B�オ�����艺�������肷��
	bool sLimit = false;		    				//��������
	BoxCharactorController m_BoxCharaCon;          //�ÓI�����I�u�W�F�N�g
	//PhysicsStaticObject m_phyStaticObject;          //�ÓI�����I�u�W�F�N�g
	float up = 0;
	float down = 0;
	bool start = false;
	bool udlimit = false;
	bool statPos = true;
	CVector3 StartPos = CVector3::Zero();
};

