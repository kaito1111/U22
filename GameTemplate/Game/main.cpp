#include "stdafx.h"
#include "system/system.h"
#include "TwoP_Pad.h"
#include "Title.h"
#include "Network/NetworkLogic.h"

extern bool g_getNetPadData;
extern bool g_isStartGame;

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

	//�l�b�g���[�N�̏������֘A���� InitGame�̒�����Ă����������H
	NetworkLogic::GetInstance().Start();
	//�J�������������B
	g_camera3D.SetPosition({ 00.0f, 100.0f, 500.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000.0f);
	g_camera3D.SetNear(10.0f);
	g_camera3D.Update();

	printf("���[���ɓ���������́A�쐬���s���Ă��܂��B\n");
	NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	printf("���[���ɓ��ꂵ�܂����B\n");

	//�^�C�g���Z���N�g����Ă܂��B
	//�^�C�g���ɕς��ė~���݂��}���A�i�C�a
	//NewGO<StageSelect>(1, "game");
	//NewGO<Game>(1, "game");
	NewGO<Title>(1, "title");
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
		//�p�b�h�̍X�V
		g_Pad[0].Update();
		
		static int frameNo = 0;
		//�l�b�g���[�N�̍X�V
		if (g_isStartGame) {
			//�p�b�h���𑊎�ɑ���B
			auto LBL = INetworkLogic().GetLBL();
			LBL->RaisePadData();
			//�Q�[�����J�n���ꂽ��p�b�h�œ������Ƃ�B
			while (true) {
				NetworkLogic::GetInstance().Update();
				if (g_getNetPadData == false) {
					//Sleep(10);
				}
				else {
					break;
				}
			}
			g_Pad[1].UpdateFromNetPadData();
			printf("frameNo = %d\n", frameNo);
			frameNo++;
		}
		else {
			NetworkLogic::GetInstance().Update();
		}
		//g_Pad[1].Update()
		g_getNetPadData = false;
		//Engine�N���X�Ƃ��ɂ܂Ƃ߂���AtkEngine�ɏ������킹�܂�
		gameObjectManager().Start();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��鏈���̌Ăяo��
		gameObjectManager().ExecuteFromGameThread();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}

	//�l�b�g���[�N����̐ؒf
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect\n");
}