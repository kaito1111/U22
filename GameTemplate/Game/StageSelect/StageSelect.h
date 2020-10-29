#pragma once
class TitleCamera;
class GamePlayer;
class Fade;
class StageSelectSprite;

class StageSelect : public IGameObject
{
	enum Dir {//����
		L,//Left�@��
		R,//Right �E
		U,//Up    ��
		D,//Down  ��
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