#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Network/NetworkLogic.h"


TwoP_Pad::TwoP_Pad() 
{

}
TwoP_Pad::~TwoP_Pad()
{
}


void TwoP_Pad::Update()
{
	if(INetworkLogic().GetLBL()->GetReady()) {
		//ゲームが開始されている
		while (g_Pad[0].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//このループはゲーム開始時にしか入らないはず。
			//バッファリングする。
			g_Pad[0].XInputStateBufferring();
			//バッファリングした内容を相手に送る。
			//パッド情報を相手に送る。
			LBLobj()->RaisePadData();
		}
		//ネットワークパッドのバッファリング。
		while (g_Pad[1].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//ここは足りなくなることがあるはずなので、ゲーム中も入る可能性がある。
			//ネットワークのアップデート。
			NetworkLogic::GetInstance().Update();
			if (LBLobj()->getReceiveFlag() == false) {
				//まだネットワークパッドのデータを受信できていない。
			}
			else {
				//ネットワークパッドのデータを受信した。
				LBLobj()->SetReceiveFlag(false);
			}
		}

		//まず新しいパッド情報をバッファリングする。
		if (g_Pad[0].GetNumBufferringXInputData() == MAX_BUFFERRING - 1) {
			//バッファリングデータが足りない。
			g_Pad[0].XInputStateBufferring();
			//バッファリングした内容を相手に送る。
			//パッド情報を相手に送る。
			LBLobj()->RaisePadData();
			//続いてネットワークパッド。
			NetworkLogic::GetInstance().Update();
		}

		//バッファリングされた情報を使ってゲームを進行させる。
		//バッファリングされた情報をもとにパッド情報を更新する。
		g_Pad[0].Update(true);
		g_Pad[1].UpdateFromNetPadData();
		//printf("Pad::Update End\n");
		m_frameNo++;
	}
	else {
		//パッドの更新
		//ゲームが開始されていない。
		//ゲーム始まってないので、バッファリング情報は使用しない。
		g_Pad[0].Update(false);
		NetworkLogic::GetInstance().Update();
	}

	LBLobj()->SetReceiveFlag(false);
}

