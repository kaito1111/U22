#pragma once
class Player;
class NPole : public IGameObject
{
public:
	NPole();
	~NPole();
	//i‚Ş•ûŒü‚ğŒˆ‚ß‚é
	void SetForward(CVector3 forward) {
		m_move = forward;
	}
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	CVector3 GetPosition() {
		return m_position;
	}
private:


	bool Start()override;
	void Update()override;
	void Draw()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	Player* m_player = nullptr;
};