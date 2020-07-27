#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"
#include"Gimmick_Button.h"
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
	void SetMoveLimit(const float& limit) {
		up =  m_pos.y + limit;
		down =m_pos.y -  limit;
	}
private:
	bool Start();
	void Update();
	void Draw();
	void Move();

	Gimmick_Button* button = nullptr;
	SkinModel m_model;								//スキンモデル
	CVector3 m_pos = CVector3::Zero();				//座標
	CQuaternion m_rot = CQuaternion::Identity();	//回転
	bool UDPos = false;								//上がり切ってるか下がり切ってるか
	bool speedDown = false;							//スピードを上げたり下げたりする
	float moveSpeed = 0;                            //速度。上がったり下がったりする
	bool fastMove = false;                          //最初に動くときのフラグ
	bool sLimit = false;		    				//動いた量
	PhysicsStaticObject m_phyStaticObject;          //静的物理オブジェクト
	SoundSource m_Se;
	CVector3 startPos = CVector3::Zero();

	void move2();
	float up = 0;
	float down = 0;
	bool start = false;
	bool udlimit = false;
	bool statPos = true;
};	

