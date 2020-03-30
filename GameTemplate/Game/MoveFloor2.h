#pragma once
#include"physics/PhysicsStaticObject.h"
class MoveFloor2 : public IGameObject
{
//左右に動くヤツやで。
public:
	MoveFloor2();
	~MoveFloor2();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}

private:
	void Draw();
	bool Start();
	void Update();
	void Move();
	
	SkinModel m_model;								//スキンモデル
	CVector3 m_pos = CVector3::Zero();				//座標
	CQuaternion m_rot = CQuaternion::Identity();	//回転
	bool UDPos = false;								//上がり切ってるか下がり切ってるか
	bool speedDown = false;							//スピードを上げたり下げたりする
	float moveSpeed = 0;                            //速度。上がったり下がったりする
	bool sLimit = false;		    				//動いた量
	PhysicsStaticObject m_phyStaticObject;          //静的物理オブジェクト
};

