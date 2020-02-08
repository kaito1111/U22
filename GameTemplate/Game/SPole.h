#pragma once
class Player;
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
	const CVector3 GetPosition() {
		return m_position;
	}
	const void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	//void magunetTask(CVector3& Position);
private:


	bool Start()override;
	void Update()override;
	void Draw()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	Player* m_player = nullptr;
	NPole* m_npole = nullptr;

	void deleteRange();
	void idou();
	void SetSPole();
};