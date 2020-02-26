#pragma once
class GameObjectScythe : public IGameObject
{
public:
	GameObjectScythe();
	~GameObjectScythe();
	bool Start();
	void Update();
	void Draw();

	void Move();//振り子運動
private:
	SkinModel m_model;							 //スキンモデル
	CVector3 m_pos = CVector3::Zero();			 //座標
	CQuaternion m_rot = CQuaternion::Identity(); //回転量
	float rot = 0.0f;                            //回転してる量
	float spinSpeed = 0.0f;						 //回転速度
	bool spinChange = false;                     //回転方向を切り替えるフラグ
	bool speedChange = false;                    //回転速度を切り替えるフラグ

};

