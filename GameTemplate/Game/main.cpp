#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Game.h"
#include "StageSelect.h"
#include "TwoP_Pad.h"
#include "Title.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	//Console
	AllocConsole();
	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);

	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 00.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(10.0f);

	g_camera3D.Update();

	//�^�C�g���Z���N�g����Ă܂��B
	//�^�C�g���ɕς��ė~���݂��}���A�i�C�a
	//NewGO<StageSelect>(1, "game");
	NewGO<Game>(1, "game");
	NewGO<TwoP_Pad>(1, "twop_pad");
	//NewGO<Title>(1, "title");
	//�J�����̏�����
	g_camera2D.Update2D();

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�T�E���h�G���W���̍X�V
		Engine().GetSoundEngine().Update();
		//Engine�N���X�Ƃ��ɂ܂Ƃ߂���AtkEngine�ɏ������킹�܂�
		gameObjectManager().Start();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��鏈���̌Ăяo��
		gameObjectManager().ExecuteFromGameThread();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}