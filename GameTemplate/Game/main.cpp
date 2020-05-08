#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Game.h"
#include "StageSelect.h"
#include "TwoP_Pad.h"
#include "Title.h"

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

	//カメラを初期化。
	g_camera3D.SetPosition({ 00.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(10.0f);

	g_camera3D.Update();

	//タイトルセレクト作ってます。
	//タイトルに変えて欲しみがマリアナ海溝
	//NewGO<StageSelect>(1, "game");
	NewGO<Game>(1, "game");
	NewGO<TwoP_Pad>(1, "twop_pad");
	//NewGO<Title>(1, "title");
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
		//Engineクラスとかにまとめた後、tkEngineに処理合わせます
		gameObjectManager().Start();
		//ゲームオブジェクトマネージャーでする処理の呼び出し
		gameObjectManager().ExecuteFromGameThread();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}