#pragma once
#include"character/CharacterController.h"
class GamePlayer;
class RorlingRock : public IGameObject
{
public:
	RorlingRock(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~RorlingRock();
	bool Start();
	void Update();
	void Rorling();
	void Move();
	void killPlayer();
	void Draw();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
private:
	GamePlayer* player1 = nullptr;
	GamePlayer* player2 = nullptr;
	SkinModel m_model;//スキンモデル
	CVector3 m_pos = CVector3::Zero();			//座標
	CVector3 m_scale = CVector3::One();			//拡大率
	CQuaternion m_rot = CQuaternion::Identity();//回転
	CharacterController charaCon;				//キャラコン
	CVector3 moveSpeed = CVector3::One();		//移動速度

	//プレイヤーの人数
	Pad m_pad[Pad::CONNECT_PAD_MAX];//Padの数だけね。
};

