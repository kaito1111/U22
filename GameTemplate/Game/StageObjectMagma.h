#pragma once
class StageObjectMagma : public IGameObject
{
public:
	StageObjectMagma();
	~StageObjectMagma();
	bool Start();
	void Update();
	void Draw();

	void PlayerKill();
private:
	CVector3 m_pos = CVector3::Zero();//座標
	SkinModel m_model;//多分エフェクトに変わるんじゃないかな

	
};