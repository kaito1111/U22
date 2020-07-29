#include "stdafx.h"
#include "PlayerPad.h"

PlayerPad::PlayerPad()
{
	//パッドの初期化
	g_Pad->Init(PadNum);
}

void PlayerPad::Update()
{
	//パッドの更新
	g_Pad[PadNum].Update();
}

bool PlayerPad::IsJump()
{
	if (g_Pad[PadNum].IsPress(enButtonA)) {
		//A
		return true;
	}
}

bool PlayerPad::IsMagN()
{
	if (g_Pad[PadNum].IsPress(enButtonX)) {
		//X
		return true;
	}
}

bool PlayerPad::IsMagS()
{
	if (g_Pad[PadNum].IsPress(enButtonY)) {
		//Y
		return true;
	}
}

bool PlayerPad::IsNoMag()
{
	if (g_Pad[PadNum].IsPress(enButtonA)) {
		//A
		return true;
	}
}

bool PlayerPad::IsMagShotN()
{
	if (g_Pad[PadNum].IsPress(enButtonRB1)) {
		//RB1
		return true;
	}
}

bool PlayerPad::IsMagShotS()
{
	if (g_Pad[PadNum].IsPress(enButtonLB1)) {
		//LB1
		return true;
	}
}