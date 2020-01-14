#pragma once
class Player;
class stageObject2:IGameObject
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

	SkinModel* m_model = nullptr;			//スキンモデル
	CVector3 m_position = CVector3::Zero();//座標


};