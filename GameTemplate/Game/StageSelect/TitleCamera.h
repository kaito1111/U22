#pragma once
class GamePlayer;class TitleCamera :public IGameObject

{
	//�^�C�g��
public:
	TitleCamera();
	~TitleCamera();
	bool Start();
	void Update();
	int GetChoiceStageNum() const
	{
		return nowChoiceStage;
	}
private:
	GamePlayer* player[g_PlayerNum];
	CVector3 m_pos = CVector3::Zero();
void Move();
	//CVector3 m_pos = CVector3::Zero();		//���W
	CVector3 m_target = CVector3::Zero();   //�����_
	int nowChoiceStage = 0;
};

