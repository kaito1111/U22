#include "stdafx.h"
#include "myEngine.h"
#include "util/tkStopwatch.h"
#include "Network/NetworkLogic.h"
#include "system/system.h"

CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::Init()
{
	//ゲームの初期化
	InitGame();
	//ネットワークの初期化関連処理 
	//ネットワークはエンジン側の処理？それとも違う何かで、処理すべき？？
	NetworkLogic::GetInstance().Start();
}

bool CEngine::Start()
{
	//ルームに入場
	printf("ルームに入場もしくは、作成を行っています。\n");
	NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	printf("ルームに入場しました。\n");

	//フォント作成。
	m_font = std::make_unique<CFont>();

	return true;
}

void CEngine::Update()
{
	//スタート
	m_sw.Start();
	//描画開始。
	Engine().GetGraphicsEngine().BegineRender();
	//物理エンジンの更新。
	g_physics.Update();
	//サウンドエンジンの更新
	Engine().GetSoundEngine().Update();
	//カメラ更新。
	g_camera3D.Update();
	g_camera2D.Update2D();

	//ネットワークの更新
	//このパッドのバッファリング処理、Player2つのパッド関連だから
	//twoP_Padで書くべき。
	if (INetworkLogic().GetLBL()->GetReady()) {
		//ゲームが開始されている
		while (g_Pad[0].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//このループはゲーム開始時にしか入らないはず。
			g_Pad[0].XInputStateBufferring();
			//バッファリングした内容を相手に送る。
			//パッド情報を相手に送る。
			LBLobj()->RaisePadData();
			m_frameNo++;
			//1フレーム分寝る。
			Sleep(TIME_ONE_FRAME);
		}
		//ネットワークパッドのバッファリング。
		while (g_Pad[1].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//ここは足りなくなることがあるはずなので、ゲーム中も入る可能性がある。
			NetworkLogic::GetInstance().Update();
			if (LBLobj()->getReceiveFlag() == false) {
				//まだネットワークパッドのデータを受信できていない。
				//1フレーム待機。
				Sleep(TIME_ONE_FRAME);
			}
			else {
				//ネットワークパッドのデータを受信した。
				LBLobj()->SetReceiveFlag(false);
			}
		}

		//バッファリングされた情報を使ってゲームを進行させる。
		//まず新しいパッド情報をバッファリングする。
		g_Pad[0].XInputStateBufferring();
		//バッファリングした内容を相手に送る。
		//パッド情報を相手に送る。
		LBLobj()->RaisePadData();
		//続いてネットワークパッド。
		NetworkLogic::GetInstance().Update();
		if (LBLobj()->getReceiveFlag() == true) {
			LBLobj()->SetReceiveFlag(false);
		}
		else {
			//このフレーム間に合わなかったとしても無視。待たない。
			//ネットワークパッドはバッファリングが枯渇したら貯める。
		}
		printf("Pad::Update Start\n");
		//バッファリングされた情報をもとにパッド情報を更新する。
		g_Pad[0].Update(true);
		g_Pad[1].UpdateFromNetPadData();
		printf("Pad::Update End\n");
		m_frameNo++;
	}
	else {
		//パッドの更新
		//ゲームが開始されていない。
		g_Pad[0].Update(false);
		NetworkLogic::GetInstance().Update();
	}

	LBLobj()->SetReceiveFlag(false);
	//Engineクラスとかにまとめた後、tkEngineに処理合わせます
	gameObjectManager().Start();
	//ゲームオブジェクトマネージャーでする処理の呼び出し
	gameObjectManager().ExecuteFromGameThread();
	//30フレーム
	static int count = 0;
	m_timeTotal += (float)m_sw.GetElapsed();
	count++;
	if (count == 30) {
		//毎回計算すると重いのかな？
		//30フレーム分の平均FPSの計算
		m_fps = 1.0f / (m_timeTotal / count);
		m_timeTotal = 0.0f;
		count = 0;
	}
	//FPSの表示。
	m_font->Begin();
	wchar_t fps[256];
	swprintf_s(fps, L"FPS = %.1f", m_fps);
	//フォント書き出し。
	m_font->Draw(
		fps,
		{
			FRAME_BUFFER_W * -0.18f,
			FRAME_BUFFER_H 
		},
		{0.0f,0.0f,0.0f,1.0f},
		0.0f,
		1.0f,
		{0.0f, 1.0f}
	);
	m_font->End();
	//描画終了。
	Engine().GetGraphicsEngine().EndRender();
	DWORD sleepTime = max(0, TIME_ONE_FRAME - m_sw.GetElapsedMillisecond());
	Sleep(sleepTime);
	//ストップ
	m_sw.Stop();
}

void CEngine::Final()
{
	//ネットワークからの切断
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect\n");
}
