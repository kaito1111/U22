#include "stdafx.h"
#include "PlayerPad.h"
#include "Network/NetworkLogic.h"

PlayerPad::PlayerPad()
{
}

void PlayerPad::Update()
{
	//パッド情報をphotonに送る
	auto LBL = INetworkLogic().GetLBL();
	//photonコンテナに積む
	LBL->putData(1, A);
	LBL->putData(2, B);
	LBL->putData(3, X);
	LBL->putData(4, Y);
	LBL->putData(5, RB1);
	LBL->putData(6, LB1);
	LBL->putData(7, vX);
	LBL->putData(8, vZ);
	//送信
	LBL->RaisePlayerData();
}