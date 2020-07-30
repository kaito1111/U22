#pragma once
class GamePlayer;
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
	void SetPlayer(GamePlayer* pl) {
		m_player = pl;
	}
private:


	bool Start()override;
	void Update()override;
	void Draw()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	GamePlayer* m_player = nullptr;
	NPole* m_npole = nullptr;

	void deleteRange();
	void idou();
	void SetSPole();
};