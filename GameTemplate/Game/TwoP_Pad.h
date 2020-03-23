#pragma once
#include "HID/Pad.h"
#include "Player.h"

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	Pad				m_pad[Pad::CONNECT_PAD_MAX];		//m_pad�̒�`�B
	SpriteRender*	m_ManualSprite = nullptr;

	const int		PlayerNum = 2;
	Player*			player[2] = {};
	bool			UpdateStop = false;					//Update���~�߂�t���Ofalse��Update����B
	//bool Start()override;
	void			Update()override;
};

