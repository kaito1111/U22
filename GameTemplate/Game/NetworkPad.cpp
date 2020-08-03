#include "stdafx.h"
#include "NetworkPad.h"
#include "Network/NetworkLogic.h"

NetworkPad::NetworkPad()
{
}

void NetworkPad::Update()
{
	vX = INetworkLogic().GetLBL()->GetMoveX();
	vZ = INetworkLogic().GetLBL()->GetMoveZ();
	g_Pad[m_PadNum].SetStickLX(vX);
}
