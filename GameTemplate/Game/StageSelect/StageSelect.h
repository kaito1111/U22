#pragma once
class TitleCamera;
class GamePlayer;
class Fade;
class StageSelectSprite;

class StageSelect : public IGameObject
{
	enum Dir {//方向
		L,//Left　左
		R,//Right 右
		U,//Up    上
		D,//Down  下
		num
	};
public:
	StageSelect();
	~StageSelect();
	bool Start();
	void Update();

private:
	void SetCameraTarget();

	TitleCamera* m_TitleCamera = nullptr;


	SkinModelRender* m_StageModel = nullptr;
	PhysicsStaticObject m_staticObj;

	GamePlayer* m_Player[2] = {};

	Fade* m_fade = nullptr;
	int StageNo = 0;

	StageSelectSprite* m_Sprite = nullptr;
	float m_SelectLen = 300.0f;
};