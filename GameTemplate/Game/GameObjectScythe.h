#pragma once
class Player;
class GameObjectScythe : public IGameObject
{
public:
	GameObjectScythe();
	~GameObjectScythe();
	bool Start();
	void Update();
	void Draw();
	void PlayerKill();
	void Move();//振り子運動
private:
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	SkinModel m_model;							 //スキンモデル
	CVector3 m_pos = CVector3::Zero();			 //座標
	CQuaternion m_rot = CQuaternion::Identity(); //回転量
	float rot = 0.0f;                            //回転してる量
	float spinSpeed = 0.0f;						 //回転速度
	bool spinChange = false;                     //回転方向を切り替えるフラグ
	bool speedChange = false;                    //回転速度を切り替えるフラグ

	//正面右下
	CVector3 m_front = CVector3::Front();
	CVector3 m_right = CVector3::Right();
	CVector3 m_up = CVector3::Up();

};

