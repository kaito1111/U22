#pragma once

extern HWND			g_hWnd ;				//ウィンドウハンドル。
extern GraphicsEngine* g_graphicsEngine ;	//グラフィックスエンジン。

//ウィンドウの初期化。
void InitGameWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
//ゲームの初期化
void InitGame();
//ウィンドウメッセージをディスパッチ。falseが返ってきたら、ゲーム終了。
bool DispatchWindowMessage();
