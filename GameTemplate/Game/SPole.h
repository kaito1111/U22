#pragma once
class Player;
class SPole : public IGameObject
{
public:

	SPole();
	void SetForward(CVector3 forward) {
		m_move = forward;
	}
private:

	~SPole();

	bool Start()override;
	void Update()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	Player* m_player = nullptr;
	int deleteTime = 0;
};