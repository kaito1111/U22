#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Game.h"
#include "Magnet/MagnetManager.h"


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	NewGO<Game>(1, "game");

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//Engineクラスとかにまとめた後、tkEngineに処理合わせます
		gameObjectManager().Start();
		//ゲームオブジェクトマネージャーでする処理の呼び出し
		gameObjectManager().ExecuteFromGameThread();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}