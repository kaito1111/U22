#pragma once
class Player;
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();

private:
	bool Start();
	void Update();
	SkinModel m_Skin;
	CVector3 m_Position = CVector3::Zero();
	Player* m_player = nullptr;
};