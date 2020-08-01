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
	auto a = twoP_Pad().GetNPad();
	g_Pad[a->m_PadNum].SetStickLX(vX);
}
