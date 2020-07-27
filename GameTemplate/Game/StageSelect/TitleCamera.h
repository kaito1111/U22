#pragma once
class StageSelect;
class TitleCamera :public IGameObject

{
	//ƒ^ƒCƒgƒ‹
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
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_target = CVector3::Zero();
	int nowChoiceStage = 0;
};

