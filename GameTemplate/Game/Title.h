#pragma once
class Fade;
class BoxCollider;
class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	void PostRender();
	/// <summary>
	/// ネットワーク関連
	/// </summary>
	void NetworkUpdate();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	void Update()override;
	SpriteRender* m_Sprite = nullptr;
	Fade* m_fade = nullptr;
	SoundSource m_bgm;
};