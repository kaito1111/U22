#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	/// <summary>
	/// �l�b�g���[�N�֘A
	/// </summary>
	void NetworkUpdate();
	void Update()override;
	SpriteRender* m_Sprite = nullptr;
	Fade* m_fade = nullptr;
	SoundSource m_bgm;
	bool DeleteTitle = false;
};