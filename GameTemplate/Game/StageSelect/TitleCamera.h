#pragma once
class GamePlayer;
class TitleCamera :public IGameObject

{
	//�^�C�g��
public:
	TitleCamera();
	~TitleCamera();
	bool Start();
	void Update();

private:
	GamePlayer* player = nullptr;
	CVector3 m_pos = CVector3::Zero();
};

