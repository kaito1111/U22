#pragma once
#include"character/CharacterController.h"
class RorlingRock : public IGameObject
{
public:
	RorlingRock();
	~RorlingRock();
	bool Start();
	void Update();
	void Rorling();
	void Move();
	void Draw();
private:
	SkinModel m_model;//スキンモデル
	CVector3 m_pos = CVector3::Zero();			//座標
	CVector3 m_scale = CVector3::One();			//拡大率
	CQuaternion m_rot = CQuaternion::Identity();//回転
	CharacterController charaCon;				//キャラコン
	CVector3 moveSpeed = CVector3::One();		//移動速度
};

