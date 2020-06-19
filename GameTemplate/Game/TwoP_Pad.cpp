#include "stdafx.h"
#include "TwoP_Pad.h"
#include "Player.h"
#include "Network/NetworkLogic.h"


TwoP_Pad::TwoP_Pad() {

	for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++)
	{
		g_Pad[i].Init(i);
	}
	m_ManualSprite = NewGO<SpriteRender>(4);
	m_ManualSprite->Init(L"Assets/sprite/manual.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_ManualSprite->SetW(m_Manual_W);
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	m_ButtonSprite = NewGO<SpriteRender>(3);
	m_ButtonSprite->Init(L"Assets/sprite/Button.dds", 250.0f, 250.0f);
	CVector3 ButtonSpritePos = { 500.0f,-250.0f,0.0f };
	m_ButtonSprite->SetPosition(ButtonSpritePos);
}
TwoP_Pad::~TwoP_Pad()
{
	//for (int i = 0; i < g_PlayerNum;i++) {
	//	DeleteGO(player[i]);
	//}
	DeleteGO(m_ManualSprite);
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
	/// <summary>
	/// ここからPadの入力値をphotonを中継して、通信相手に送るコード
	/// </summary>

	int PlayerPad = 0;
	g_Pad[PlayerPad].Update();
	//先に他プレイヤーからのPadの受け取り
	PlayerPad = NetworkLogic::GetInstance().GetLBL()->GetplayerNum();
	if (NetworkLogic::GetInstance().GetLBL()->GetPlayerPadData(enButtonNum) == 1) {//パッドが更新されているかどうか
		switch (PlayerPad)
		{
		case 0:
			for (int i = 0; i < enButtonNum; i++)
			{
				g_Pad[1].SetPadButton(NetworkLogic::GetInstance().GetLBL()->GetPlayerPadData(i), i);
			}
			g_Pad[1].SetStickLX(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickLXData());
			g_Pad[1].SetStickLY(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickLYData());
			g_Pad[1].SetStickRX(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickRXData());
			g_Pad[1].SetStickLX(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickRYData());
			break;
		default:

			for (int i = 0; i < enButtonNum; i++)
			{
				g_Pad[1].SetPadButton(g_Pad[0].GetPress(i), i);
				g_Pad[0].SetPadButton(NetworkLogic::GetInstance().GetLBL()->GetPlayerPadData(i), i);
			}
			g_Pad[1].SetStickLX(g_Pad[0].GetLStickXF());
			g_Pad[1].SetStickLY(g_Pad[0].GetLStickYF());
			g_Pad[1].SetStickRX(g_Pad[0].GetRStickXF());
			g_Pad[1].SetStickRY(g_Pad[0].GetRStickYF());
			g_Pad[0].SetStickLX(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickLXData());
			g_Pad[0].SetStickLY(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickLYData());
			g_Pad[0].SetStickRX(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickRXData());
			g_Pad[0].SetStickRY(NetworkLogic::GetInstance().GetLBL()->GetPlayerStickRYData());
			break;
		}
	}
	//ほかのプレイヤーのパッドを受け取ったので自分のパッドを送る
	//自分のPadの更新と送信
	//for (int i = 0; i < Pad::CONNECT_PAD_MAX; i++) {
	//g_Pad[PlayerPad].SetPadButton(1, 0);
	//if (i < g_PlayerNum) {
	if (g_Pad[PlayerPad].IsTrigger(enButtonStart)
		//&&player[i]->GetUpdate()
		)
	{
		if (m_Manual_W == 0.0f)
		{
			m_Manual_W = 1.0f;
			m_ManualSprite->SetW(m_Manual_W);
			//player[i]->SetUpdate(false);
		}
		else
		{
			m_Manual_W = 0.0f;
			m_ManualSprite->SetW(m_Manual_W);
			//player[i]->SetUpdate(true);
		}
	}
	//}
	bool IsAllPad[EnButton::enButtonNum + 1] = {};
	IsAllPad[EnButton::enButtonNum] = 1;
	NetworkLogic::GetInstance().GetLBL()->putData(EnButton::enButtonNum, IsAllPad[EnButton::enButtonNum]);		//更新した
	//padボタンの個数分まわす
	for (int PadNo = 0; PadNo < EnButton::enButtonNum; PadNo++) 
	{
		IsAllPad[PadNo] = g_Pad[PlayerPad].GetPress(PadNo);
		//ネットワークのリストにツムツム
		NetworkLogic::GetInstance().GetLBL()->putData(PadNo, IsAllPad[PadNo]);
	}

	//スティックの入力値転送コード
	float AllStick[4] = {};
	//スティックの入力値の取得
	AllStick[0] = g_Pad[PlayerPad].GetLStickXF();
	AllStick[1] = g_Pad[PlayerPad].GetRStickXF();
	AllStick[2] = g_Pad[PlayerPad].GetLStickYF();
	AllStick[3] = g_Pad[PlayerPad].GetRStickYF();

	if (AllStick[0] != 0) {
		auto a = AllStick[0];
	}
	//イベントコンテナに積む準備 keyの番号合わせるためにi+18
	for (int i = 0; i < 4; i++)
	{
		NetworkLogic::GetInstance().GetLBL()->putData(i + 18, AllStick[i]);
	}
	g_Pad[1].Update();
	//イベントの起動
	NetworkLogic::GetInstance().GetLBL()->RaisePlayerData();
}
//}
