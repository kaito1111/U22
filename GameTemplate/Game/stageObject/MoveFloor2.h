#pragma once
#include"physics/PhysicsStaticObject.h"
#include"Gimmick_Button.h"
#include "character/BoxCharactorController.h"
class MoveFloor2 : public IGameObject
{
//左右に動くヤツやで。
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
	SkinModel m_model;								//スキンモデル
	CVector3 m_pos = CVector3::Zero();				//座標
	CQuaternion m_rot = CQuaternion::Identity();	//回転
	CVector3 m_Scale = CVector3::One();
	bool UDPos = false;								//上がり切ってるか下がり切ってるか
	bool speedDown = false;							//スピードを上げたり下げたりする
	float moveSpeed = 0;                            //速度。上がったり下がったりする
	bool sLimit = false;		    				//動いた量
	BoxCharactorController m_BoxCharaCon;          //静的物理オブジェクト
	//PhysicsStaticObject m_phyStaticObject;          //静的物理オブジェクト
	float up = 0;
	float down = 0;
	bool start = false;
	bool udlimit = false;
	bool statPos = true;
	CVector3 StartPos = CVector3::Zero();
};

