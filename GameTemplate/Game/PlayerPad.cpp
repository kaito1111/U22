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
	if (LBL->GetPlayerNum() == 1) {
		//player1だった
		//photonコンテナに積む
		LBL->putData(1, A);
		LBL->putData(2, B);
		LBL->putData(3, X);
		LBL->putData(4, Y);
		LBL->putData(5, RB1);
		LBL->putData(6, LB1);
		LBL->putData(7, 1.0f);
	}
	else if (LBL->GetPlayerNum() == 2) {
		//player2だった
		//photonコンテナに積む
		LBL->putData(8, A);
		LBL->putData(9, B);
		LBL->putData(10, X);
		LBL->putData(11, Y);
		LBL->putData(12, RB1);
		LBL->putData(13, LB1);
		LBL->putData(14, 1.0f);
	}
	LBL->putData(8, vZ);
	//送信
	LBL->RaisePlayerData();
}