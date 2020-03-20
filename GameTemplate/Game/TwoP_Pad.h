#pragma once
#include "HID/Pad.h"

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	Pad m_pad[Pad::CONNECT_PAD_MAX];		//m_padの定義。
	SpriteRender* m_ManualSprite = nullptr;
	bool IsPad = true;						//パッド更新している？
	//bool Start()override;
	void Update()override;
};

