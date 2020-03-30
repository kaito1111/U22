#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"

class Player;
class moveFloor : public IGameObject
{
	//サイズ200*200*20
public:
	moveFloor(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~moveFloor();

	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
	void SetUp(bool up) {

	}
private:
	bool Start();
	void Update();
	void Draw();
	void Move();
	SkinModel m_model;								//スキンモデル
	CVector3 m_pos = CVector3::Zero();				//座標
	CQuaternion m_rot = CQuaternion::Identity();	//回転
	bool UDPos = false;								//上がり切ってるか下がり切ってるか
	bool speedDown = false;							//スピードを上げたり下げたりする
	float moveSpeed = 0;                            //速度。上がったり下がったりする
	bool sLimit = false;		    				//動いた量
	PhysicsStaticObject m_phyStaticObject;          //静的物理オブジェクト
	SoundSource m_Se;

};	

