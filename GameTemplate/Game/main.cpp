#include "stdafx.h"
#include "system/system.h"
#include "TwoP_Pad.h"
#include "Title.h"
#include "Network/NetworkLogic.h"

extern bool g_getNetPadData;
extern bool g_isStartGame;

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

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//物理エンジンの更新。
		g_physics.Update();
		//サウンドエンジンの更新
		Engine().GetSoundEngine().Update();
		//パッドの更新
		g_Pad[0].Update();
		
		static int frameNo = 0;
		//ネットワークの更新
		if (g_isStartGame) {
			//パッド情報を相手に送る。
			auto LBL = INetworkLogic().GetLBL();
			LBL->RaisePadData();
			//ゲームが開始されたらパッドで同期をとる。
			while (true) {
				NetworkLogic::GetInstance().Update();
				if (g_getNetPadData == false) {
					//Sleep(10);
				}
				else {
					break;
				}
			}
			g_Pad[1].UpdateFromNetPadData();
			printf("frameNo = %d\n", frameNo);
			frameNo++;
		}
		else {
			NetworkLogic::GetInstance().Update();
		}
		//g_Pad[1].Update()
		g_getNetPadData = false;
		//Engineクラスとかにまとめた後、tkEngineに処理合わせます
		gameObjectManager().Start();
		//ゲームオブジェクトマネージャーでする処理の呼び出し
		gameObjectManager().ExecuteFromGameThread();
		//描画終了。
		g_graphicsEngine->EndRender();
	}

	//ネットワークからの切断
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect\n");
}