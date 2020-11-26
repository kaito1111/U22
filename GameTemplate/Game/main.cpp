#include "stdafx.h"
#include "system/system.h"
#include "Manual.h"
#include "Title.h"

/*
	8/10~ mainでエンジン関連の初期化まで行うのは、違うと思うので
	Engineクラスの方に、処理を移譲しました。
*/

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	//Console
	//AllocConsole();
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
	//ウィンドウの初期化。
	InitGameWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	//エンジンの初期化。
	Engine().Init();
	//エンジンスタート。
	Engine().Start();

	//タイトルセレクト作ってます。
	//タイトルに変えて欲しみがマリアナ海溝
	//NewGO<StageSelect>(1, "game");
	//NewGO<Game>(1, "game");
	NewGO<Manual>(0, "manual");
	NewGO<Title>(1, "title");


	/*
	ここでのカメラ初期化おかしくない？
	Gameとかで使うんだから、そこですべきなのでは？
	*/
	g_camera3D.SetPosition({ 00.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(10.0f);

	while (DispatchWindowMessage() == true)
	{
		//エンジンの更新を開始。
		Engine().Update();
	}
	//エンジン終了処理。
	Engine().Final();

}