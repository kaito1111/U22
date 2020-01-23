#pragma once
#include"character/CharacterController.h"
class Player;
class iwa : IGameObject
{
public:
	iwa();
	~iwa();
	void Update();
	CVector3 GetPos() {
		return m_position;
	}
	void SetPos(CVector3 pos) {
		m_position = pos;
	}
private:
	Player* player = nullptr;
	SkinModel m_model;							//�X�L�����f��
	CVector3 m_position = CVector3::Zero();		//���W
	CharacterController m_characon;			    //�L�����R��
	CQuaternion m_Rot = CQuaternion::Identity();//��]
	
};

