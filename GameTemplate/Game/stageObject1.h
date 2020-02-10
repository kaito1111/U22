#pragma once
#include "GameObject/IGameObject.h"
#include "character/CharacterController.h"
class Player;
class stageObject1 : public IGameObject
{
	//ドッスン棘やで。
public:
	stageObject1();
	~stageObject1();
	bool Start();
	void Update();
	CVector3 GetTogePos() { //座標の取得。
		return m_position;  //当たり判定とかで使う予定。
	}
private:

	Player* player[4] = {};
	int MaxPlayer;//プレイヤーの最大数
	int PadNum;

	SkinModel m_model;  //スキンモデル

	CharacterController m_characon;

	CVector3 m_position = {0.0f,3200.0f,0.0f}; //座標。

	CVector3 moveUpDown = CVector3::Zero();//上下に動かす。

	int timer = 0;     //動かした後にちょっと止める。 

	void Draw();

	void Move();//動かすぞ

	bool UpDown = false;
};

