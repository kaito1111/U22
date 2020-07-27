#pragma once
class Player;

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//���C��RTV�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
	SpriteRender* m_ManualSprite = nullptr;

	bool UpdateStop = true;			//Update���~�߂�t���Ofalse��Update����B
	void Update()override;
	bool NewGOPlayer = false;		//�v���C���[��NewGO���邩�ǂ���
	float m_Manual_W = 0.0f;
	SpriteRender* m_ButtonSprite = nullptr;
};
