#pragma once
#include "HID/Pad.h"
class Player;

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	SpriteRender*	m_ManualSprite = nullptr;

	//Player*			player[2] = {};
	bool			UpdateStop = true;			//Updateを止めるフラグfalseでUpdateする。
	//bool			Start()override;
	void			Update()override;
	bool			NewGOPlayer = false;		//プレイヤーをNewGOするかどうか
};
