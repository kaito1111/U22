#pragma once
#include "HID/Pad.h"

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	Pad m_pad[Pad::CONNECT_PAD_MAX];		//m_pad�̒�`�B
	SpriteRender* m_ManualSprite = nullptr;
	bool IsPad = true;						//�p�b�h�X�V���Ă���H
	//bool Start()override;
	void Update()override;
};

