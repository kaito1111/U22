#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Game.h"
#include "StageSelect.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//タイトルセレクト作ってます。
	//タイトルに変えて欲しみがマリアナ海溝
	NewGO<StageSelect>(1, "game");

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