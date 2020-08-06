#pragma once
class Manual : public IGameObject
{
public:
	Manual();
	~Manual();

private:
	bool Start() override;
	void Update();
	float m_Manual_W = 0.0f;
	SpriteRender* m_ButtonSprite = nullptr;//�E���̃{�^���̊G
	SpriteRender* m_ManualSprite = nullptr;//�}�j���A���̊G
};