#pragma once
class Player;
class NPole : public IGameObject
{
public:
	NPole();
	~NPole();
	//i‚Ş•ûŒü‚ğŒˆ‚ß‚é
	void SetMoveDir(CVector3 forward) {
		m_move = forward;
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

	void deleteRange();
	void Move();
	void SetNPole();
};