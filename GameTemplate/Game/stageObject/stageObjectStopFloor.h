#pragma once
#include"physics/PhysicsStaticObject.h"
class GamePlayer;
class Floor;
class stageObjectStopFloor : public IGameObject
{
public:
	//stageObjectStopFloor();
	stageObjectStopFloor(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/);
	~stageObjectStopFloor();
	bool Start();
	void Update();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
private:
	Floor* floor = nullptr;
	GamePlayer* m_player[2] = {};//プレイヤークラスの初期化
	SkinModel m_model;        //通る前のモデル
	CVector3 playerPosition1 = CVector3::Zero();//player1の座標
	CVector3 playerPosition2 = CVector3::Zero();//player2の座標
	CVector3 m_pos = CVector3::Zero();          //自分の座標
	CQuaternion m_rot = CQuaternion::Identity();//回転
	PhysicsStaticObject atarriHantei;			//静的物理オブジェクト
	bool upFlag = false;
	bool NewGOModel = false;
};

