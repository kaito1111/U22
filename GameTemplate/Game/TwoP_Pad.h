#pragma once
#include "HID/Pad.h"

class TwoP_Pad: public IGameObject
{
	TwoP_Pad();
	~TwoP_Pad();


	Pad m_pad[Pad::CONNECT_PAD_MAX];		//m_pad�̒�`�B
	bool Start();
	void Update()override;
};

