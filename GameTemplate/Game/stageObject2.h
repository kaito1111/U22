#pragma once
class Player;
class stageObject2: public IGameObject
{
public:
	stageObject2();
	~stageObject2();
	bool Start();
	void Update();
	CVector3 GetMarutogePosition() {//座標を取る
		return m_position;
	};

	Player* player = nullptr;//プレイヤークラス
private:

	SkinModel* m_model = nullptr;			         //スキンモデル
	CVector3 m_position = CVector3::Zero();          //座標
	CQuaternion m_rotation = CQuaternion::Identity();//回転
	CVector3 scale = CVector3::One();				 //拡大
	void Draw();

};