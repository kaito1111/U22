#pragma once
class TitleCamera :public IGameObject
{
	//�^�C�g��
public:
	TitleCamera();
	~TitleCamera();
	bool Start();
	void Update();

private:
	CVector3 m_pos = CVector3::Zero();
};

