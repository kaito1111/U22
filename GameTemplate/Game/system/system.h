#pragma once

extern HWND			g_hWnd ;				//�E�B���h�E�n���h���B

//�E�B���h�E�̏������B
void InitGameWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
//�Q�[���̏�����
void InitGame();
//�E�B���h�E���b�Z�[�W���f�B�X�p�b�`�Bfalse���Ԃ��Ă�����A�Q�[���I���B
bool DispatchWindowMessage();
