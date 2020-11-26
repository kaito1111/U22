#include "stdafx.h"
#include "system/system.h"
#include "Manual.h"
#include "Title.h"

/*
	8/10~ main�ŃG���W���֘A�̏������܂ōs���̂́A�Ⴄ�Ǝv���̂�
	Engine�N���X�̕��ɁA�������ڏ����܂����B
*/

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	//Console
	//AllocConsole();
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
	//�E�B���h�E�̏������B
	InitGameWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	//�G���W���̏������B
	Engine().Init();
	//�G���W���X�^�[�g�B
	Engine().Start();

	//�^�C�g���Z���N�g����Ă܂��B
	//�^�C�g���ɕς��ė~���݂��}���A�i�C�a
	//NewGO<StageSelect>(1, "game");
	//NewGO<Game>(1, "game");
	NewGO<Manual>(0, "manual");
	NewGO<Title>(1, "title");


	/*
	�����ł̃J�������������������Ȃ��H
	Game�Ƃ��Ŏg���񂾂���A�����ł��ׂ��Ȃ̂ł́H
	*/
	g_camera3D.SetPosition({ 00.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(10.0f);

	while (DispatchWindowMessage() == true)
	{
		//�G���W���̍X�V���J�n�B
		Engine().Update();
	}
	//�G���W���I�������B
	Engine().Final();

}