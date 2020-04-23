#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	void Update()override;
	SpriteRender* m_Sprite = nullptr;
	Fade* m_fade = nullptr;
	SoundSource m_bgm;
	bool DeleteTitle = false;
};