#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//���C��RTV�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
	void Update()override;
	SpriteRender* m_Sprite = nullptr;
	Fade* m_fade = nullptr;
	SoundSource m_bgm;
	bool DeleteTitle = false;
};