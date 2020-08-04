#include "stdafx.h"
#include "system/system.h"
#include "TwoP_Pad.h"
#include "Title.h"
#include "Network/NetworkLogic.h"
#include "util/tkStopwatch.h"

extern bool g_getNetPadData;
extern bool g_isStartGame;
int g_frameNo = 0;

const DWORD TIME_ONE_FRAME = 32;	//1フレームの時間(単位:ミリ秒)。
const int MAX_BUFFERRING = 5;
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	//Console
	AllocConsole();
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//ネットワークの初期化関連処理 InitGameの中入れてもいいかも？
	NetworkLogic::GetInstance().Start();
	//カメラを初期化。
	g_camera3D.SetPosition({ 00.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(10.0f);
	g_camera3D.Update();

	printf("ルームに入場もしくは、作成を行っています。\n");
	NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	printf("ルームに入場しました。\n");

	//タイトルセレクト作ってます。
	//タイトルに変えて欲しみがマリアナ海溝
	//NewGO<StageSelect>(1, "game");
	//NewGO<Game>(1, "game");
	NewGO<Title>(1, "title");
	//カメラの初期化
	g_camera2D.Update2D();
	CStopwatch sw;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		sw.Start();
		//描画開始。
		g_graphicsEngine->BegineRender();
		//物理エンジンの更新。
		g_physics.Update();
		//サウンドエンジンの更新
		Engine().GetSoundEngine().Update();
		
		
		//ネットワークの更新
		if (g_isStartGame) {
			while (g_Pad[0].GetNumBufferringXInputData() < MAX_BUFFERRING) {
				//このループはゲーム開始時にしか入らないはず。
				g_Pad[0].XInputStateBufferring();
				//バッファリングした内容を相手に送る。
				//パッド情報を相手に送る。
				auto LBL = INetworkLogic().GetLBL();
				LBL->RaisePadData();
				g_frameNo++;
				//1フレーム分寝る。
				Sleep(TIME_ONE_FRAME);
			}
			//ネットワークパッドのバッファリング。
			while (g_Pad[1].GetNumBufferringXInputData() < MAX_BUFFERRING) {
				//ここは足りなくなることがあるはずなので、ゲーム中も入る可能性がある。
				NetworkLogic::GetInstance().Update();
				if (g_getNetPadData == false) {
					Sleep(TIME_ONE_FRAME);
				}
				else {
					
					g_getNetPadData = false;
				}
			}
			
			//バッファリングされた情報を使ってゲームを進行させる。
			//まず新しいパッド情報をバッファリングする。
			g_Pad[0].XInputStateBufferring();
			//バッファリングした内容を相手に送る。
			//パッド情報を相手に送る。
			auto LBL = INetworkLogic().GetLBL();
			LBL->RaisePadData();
			//続いてネットワークパッド。
			NetworkLogic::GetInstance().Update();
			if (g_getNetPadData == true) {
				
				g_getNetPadData = false;
			}
			else {
				//このフレーム間に合わなかったとしても無視。待たない。
				//ネットワークパッドはバッファリングが枯渇したら貯める。
			}
			//バッファリングされた情報をもとにパッド情報を更新する。
			g_Pad[0].Update(true);
			g_Pad[1].UpdateFromNetPadData();

			g_frameNo++;
		}
		else {
			//パッドの更新
			g_Pad[0].Update(false);
			NetworkLogic::GetInstance().Update();
		}
		
		g_getNetPadData = false;
		//Engineクラスとかにまとめた後、tkEngineに処理合わせます
		gameObjectManager().Start();
		//ゲームオブジェクトマネージャーでする処理の呼び出し
		gameObjectManager().ExecuteFromGameThread();
		//描画終了。
		g_graphicsEngine->EndRender();
		sw.Stop();
		DWORD sleepTime = max(0, TIME_ONE_FRAME - sw.GetElapsedMillisecond());
		Sleep(sleepTime);
	}

	//ネットワークからの切断
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect\n");
}