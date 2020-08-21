#pragma once
class Fade;

class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	void Update()override;
	SpriteRender* m_Sprite = nullptr;
	Fade* m_fade = nullptr;
	SoundSource m_bgm;
	CFontRender* m_fontRender = nullptr;	//フォントレンダー
	wchar_t m_text[32];						//フォント用のテキスト
	CVector2 m_fontPos = { 0.0f, -80.0f };
	bool DeleteTitle = false;
};