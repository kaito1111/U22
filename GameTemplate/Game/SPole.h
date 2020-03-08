#pragma once
class Player;
class NPole;

class SPole : public IGameObject
{
public:

	SPole();
	~SPole();
	//i‚Ş•ûŒü‚ğŒˆ‚ß‚é
	const void SetMoveDir(CVector3 MoveDir) {
		m_move = MoveDir;
	}
	void SetPlayer(Player* pl) {
		m_player = pl;
	}
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