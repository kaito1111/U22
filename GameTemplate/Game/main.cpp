#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Game.h"
#include "Magnet/MagnetManager.h"


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	NewGO<Game>(1, "game");

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//Engine�N���X�Ƃ��ɂ܂Ƃ߂���AtkEngine�ɏ������킹�܂�
		gameObjectManager().Start();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��鏈���̌Ăяo��
		gameObjectManager().ExecuteFromGameThread();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}