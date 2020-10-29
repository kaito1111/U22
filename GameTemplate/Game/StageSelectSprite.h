#pragma once
class GamePlayer;

class StageSelectSprite : public IGameObject
{
public:
	StageSelectSprite();
	~StageSelectSprite();

	CVector3 GetSpritePos1() {
		return m_Stage1SpritePos;
	}

	CVector3 GetSpritePos2() {
		return m_Stage2SpritePos;
	}

private:
	bool Start()override;
	void Update()override;

	SpriteRender* m_Stage1Sprite = nullptr;             //スプライト
	SpriteRender* m_Stage2Sprite = nullptr;
	CVector3 m_Stage1SpritePos = { 0.0f,100.0f ,-100.0f };              //スプライトの座標。
	CVector3 m_Stage2SpritePos = { -650.0f,200.0f ,-200.0f };

	SpriteRender* m_SelectSprite = nullptr;
	CVector3 m_SelectSpritePos = CVector3::Zero();
	float m_SelectLen = 200.0f;

	GamePlayer* m_Player = nullptr;
};