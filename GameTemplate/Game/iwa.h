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
	SkinModel m_model;							//スキンモデル
	CVector3 m_position = CVector3::Zero();		//座標
	CharacterController m_characon;			    //キャラコン
	CQuaternion m_Rot = CQuaternion::Identity();//回転
	
};

