#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "level/Level.h"

//�����̊m�F

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	//�v���C���[
	Player* player = NewGO<Player>(0, "Player");
	//DeleteGO(player);
	
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
		//���Start������tkEngine�ɍ��킹�܂�
		gameObjectManager().Start();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��鏈��
		gameObjectManager().ExecuteFromGameThread();
		//�J�����̍X�V�B
		g_camera3D.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}