#pragma once
class Player;
class TitleCamera :public IGameObject

{
	//�^�C�g��
public:
	TitleCamera();
	~TitleCamera();
	bool Start();
	void Update();

private:
	Player* player = nullptr;
	CVector3 m_pos = CVector3::Zero();
};

