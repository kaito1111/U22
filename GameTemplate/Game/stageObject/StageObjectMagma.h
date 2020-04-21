#pragma once
class Player;
class StageObjectMagma : public IGameObject
{
public:
	StageObjectMagma(/*const wchar_t* modelName, CVector3 pos, CQuaternion rot*/);
	~StageObjectMagma();
	bool Start();
	void Update();
	void Draw();
	void SetPosition(const CVector3& pos) {
		m_pos = pos;
	}
	void PlayerKill();
private:
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	CVector3 m_pos = CVector3::Zero();//座標
	SkinModel m_model;//多分エフェクトに変わるんじゃないかな
	CQuaternion m_rot = CQuaternion::Identity();

	
};