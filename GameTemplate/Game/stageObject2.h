#pragma once
#include"character/CharacterController.h"
class Player;
class stageObject2: public IGameObject
{
	//転がってくる岩
	//大きさは半径200ｃｍの球体、凹凸は無し
	//visualStudioで200と記入すればちょうど半径と同じ長さが取れます
public:
	stageObject2();
	~stageObject2();
	bool Start();
	void Update();
	void Rorling();
	CVector3 GetMarutogePosition() {//座標を取る
		return m_pos;
	};

	Player* player = nullptr;//プレイヤークラス
private:

	SkinModel* m_model = nullptr;			    //スキンモデル
	CVector3 m_pos = CVector3::Zero();          //座標
	CQuaternion m_rot = CQuaternion::Identity();//回転
	CVector3 scale = CVector3::One();			//拡大
	CharacterController charaCon;				//キャラコン
	CVector3 moveSpeed = CVector3::Zero();		//移動速度
	void Draw();

};