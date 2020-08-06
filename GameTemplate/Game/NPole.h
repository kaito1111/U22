#pragma once
class GamePlayer;
class NPole : public IGameObject
{
public:
	NPole();
	~NPole();
	//êiÇﬁï˚å¸ÇåàÇﬂÇÈ
	void SetMoveDir(CVector3 forward) {
		m_move = forward;
	}
	void SetSpownPos(CVector3 pos) {
		m_SpownPos = pos;
	}
private:


	bool Start()override;
	void Update()override;
	void Draw()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	CVector3 m_SpownPos = CVector3::Zero();

	void deleteRange();
	void Move();
	void SetNPole();
};