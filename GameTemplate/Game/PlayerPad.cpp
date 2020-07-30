#include "stdafx.h"
#include "PlayerPad.h"

PlayerPad::PlayerPad()
{
}

void PlayerPad::Init(int PadNum)
{
	//パッドの初期化
	g_Pad[PadNum].Init(PadNum);
	m_PadNum = PadNum;
}

void PlayerPad::Update()
{
	//パッドの更新
	g_Pad[0].Update();
}

bool PlayerPad::IsJump()
{
	if (g_Pad[m_PadNum].IsPress(enButtonA)) {
		//A
		return true;
	}
}

bool PlayerPad::IsMagN()
{
	if (g_Pad[m_PadNum].IsPress(enButtonX)) {
		//X
		return true;
	}
}

bool PlayerPad::IsMagS()
{
	if (g_Pad[m_PadNum].IsPress(enButtonY)) {
		//Y
		return true;
	}
}

bool PlayerPad::IsNoMag()
{
	if (g_Pad[m_PadNum].IsPress(enButtonA)) {
		//A
		return true;
	}
}

bool PlayerPad::IsMagShotN()
{
	if (g_Pad[m_PadNum].IsPress(enButtonRB1)) {
		//RB1
		return true;
	}
}

bool PlayerPad::IsMagShotS()
{
	if (g_Pad[m_PadNum].IsPress(enButtonLB1)) {
		//LB1
		return true;
	}
}

bool PlayerPad::IsTriStart()
{
	if (g_Pad[m_PadNum].IsPress(enButtonStart)) {
		//start
		return true;
	}
}