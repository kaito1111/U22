#include "stdafx.h"
#include "PlayerPad.h"
#include "Network/NetworkLogic.h"

PlayerPad::PlayerPad()
{
}

void PlayerPad::Update()
{
	//�p�b�h����photon�ɑ���
	auto LBL = INetworkLogic().GetLBL();
	//photon�R���e�i�ɐς�
	LBL->putData(1, A);
	LBL->putData(2, B);
	LBL->putData(3, X);
	LBL->putData(4, Y);
	LBL->putData(5, RB1);
	LBL->putData(6, LB1);
	LBL->putData(7, vX);
	LBL->putData(8, vZ);
	//���M
	LBL->RaisePlayerData();
}