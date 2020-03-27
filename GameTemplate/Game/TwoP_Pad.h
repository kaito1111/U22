#pragma once
#include "HID/Pad.h"
#include "Player.h"

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	Pad				m_pad[Pad::CONNECT_PAD_MAX];		//m_padの定義。
	SpriteRender*	m_ManualSprite = nullptr;

	Player*			player[2] = {};
	bool			UpdateStop = true;					//Updateを止めるフラグfalseでUpdateする。
	//bool Start()override;
	void			Update()override;
};

