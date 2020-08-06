#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"
#include "PlayerPad.h"
#include "NetworkPad.h"
#include "Network/NetworkLogic.h"


TwoP_Pad::TwoP_Pad() 
{
	//for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++)
	//{
	//	g_Pad[i].Init(i);
	//}

	//パッド番号の取得
	m_PlayerPadNum = NetworkLogic::GetInstance().GetLBL()->GetPlayerNum();
	//各Padのインスタンス化
	//padのポリモーフィズム
	m_playerPad = NewGO<PlayerPad>(0);
	m_networkPad = NewGO<NetworkPad>(0);
	//パッドの識別をして初期化
	if (m_PlayerPadNum == 1) {
		//player1だった
		m_playerPad->Init(0);
		m_networkPad->Init(1);
	}
	else if (m_PlayerPadNum == 2) {
		//player2だった
		m_playerPad->Init(0);
		m_networkPad->Init(1);
	}

}
TwoP_Pad::~TwoP_Pad()
{
	//for (int i = 0; i < g_PlayerNum;i++) {
	//	DeleteGO(player[i]);
	//}
}

void TwoP_Pad::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}

//bool TwoP_Pad::Start()
//{
//
//		return true;
//	
//	return false;
//}

void TwoP_Pad::Update()
{
	//if (INetworkLogic().GetLBL()->GetReady()) {
	//	//通信の準備ＯＫや　PadのUpdateかいしぃ！
	//	//そこまでやで。。
	//	INetworkLogic().GetLBL()->SetReady(false);
	//}
	//m_playerPad->Update();

	//INetworkLogic().GetLBL()->putData(Jump, m_playerPad->IsJump());
	if (m_playerPad->IsTriStart())
	{
	}
}

