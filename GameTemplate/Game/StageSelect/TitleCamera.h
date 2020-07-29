#pragma once
class StageSelect;
class TitleCamera :public IGameObject

{
	//タイトル
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
	StageSelect* stageSelect = nullptr;
	void Move();
	CVector3 m_pos = CVector3::Zero();		//座標
	CVector3 m_target = CVector3::Zero();   //注視点
	int nowChoiceStage = 0;
};

