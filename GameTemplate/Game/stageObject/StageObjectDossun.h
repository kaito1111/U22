#pragma once
#include"physics/PhysicsStaticObject.h"
class GamePlayer;
class StageObjectDossun : public IGameObject
{
public:
	StageObjectDossun(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~StageObjectDossun();
	bool Start();
	void Update();
	void Draw();
	void Move();
	void playerKill();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
private:
	GamePlayer* player1 = nullptr;
	GamePlayer* player2 = nullptr;
	SkinModel m_model;                          //スキンモデル
	CVector3 startPos = CVector3::Zero();		//初期座標を保存する
	CVector3 m_pos = CVector3::Zero();			//座標
	CVector3 oldPos = CVector3::Zero();         //落下時に進んでるか見るための座標
	CQuaternion m_rot = CQuaternion::Identity();//回転量
	PhysicsStaticObject staticObject;			//静的物理オブジェクト
	bool Up = true;								//上にいるかの判定
	bool Down = false;	                        //下にイルカの判定
	bool leftRight = false;						//左右に揺らすためのフラグ
	int count = 0;                              //時間のカウント
	int yurashitaCount = 0;                     //揺らした回数を保存する変数     
	int  NextGataGata = 0;                      //再度動き出すためのフラグ

	
};

