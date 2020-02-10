#pragma once
#include"physics/RigidBody.h"
#include"physics/PhysicsStaticObject.h"

class Player;
class moveFloor : public IGameObject
{
	//サイズ200*200*20
public:
	//moveFloor(const wchar_t* modelName, CVector3 pos, CQuaternion rot);
	moveFloor();
	~moveFloor();

	void Draw();
	bool Start();
	void Update();
	void Move();
	void SetBoxDot();         //直方体の４頂点の座標
	void CollisionDetection();//プレイヤーとの当たり判定
private:
	Player* player[4] = {};
	int MaxPlayer;//プレイヤーの最大数
	SkinModel m_model;								//スキンモデル
	CVector3 m_pos = CVector3::Zero();				//座標
	CQuaternion m_rot = CQuaternion::Identity();	//回転
	bool UDPos= false;								//上がり切ってるか下がり切ってるか
	bool speedDown = false;							//スピードを上げたり下げたりする
	float moveSpeed = 0;                            //速度。上がったり下がったりする
	bool sLimit = false;		    				//動いた量
	PhysicsStaticObject m_phyStaticObject;          //静的物理オブジェクト


	//ボックスの色々

	//前
	CVector3 FrontRightUp = CVector3::Zero();  //右上
	CVector3 FrontRightDown = CVector3::Zero();//右下
	CVector3 FrontLeftUp = CVector3::Zero();   //左上
	CVector3 FrontLeftDown = CVector3::Zero(); //左下

	//後ろ
	CVector3 BackRightUp = CVector3::Zero();  //右上
	CVector3 BackRightDown = CVector3::Zero();//右下
	CVector3 BackLeftUp = CVector3::Zero();   //左上
	CVector3 BackLeftDown = CVector3::Zero(); //左下

};	

