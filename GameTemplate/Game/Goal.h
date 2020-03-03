#pragma once
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();

private:
	SkinModel m_Skin;
	CVector3 m_Position = CVector3::Zero();

};