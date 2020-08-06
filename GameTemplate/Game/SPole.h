#pragma once
class GamePlayer;
class NPole;

class SPole : public IGameObject
{
public:

	SPole();
	~SPole();
	//êiÇﬁï˚å¸ÇåàÇﬂÇÈ
	const void SetMoveDir(CVector3 MoveDir) {
		m_move = MoveDir;
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
	NPole* m_npole = nullptr;

	void deleteRange();
	void idou();
	void SetSPole();
};