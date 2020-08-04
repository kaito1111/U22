#include "stdafx.h"
#include "system/system.h"
#include "TwoP_Pad.h"
#include "Title.h"
#include "Network/NetworkLogic.h"
#include "util/tkStopwatch.h"

extern bool g_getNetPadData;
extern bool g_isStartGame;
int g_frameNo = 0;

const DWORD TIME_ONE_FRAME = 32;	//1�t���[���̎���(�P��:�~���b)�B
const int MAX_BUFFERRING = 5;
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
	CStopwatch sw;
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		sw.Start();
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�T�E���h�G���W���̍X�V
		Engine().GetSoundEngine().Update();
		
		
		//�l�b�g���[�N�̍X�V
		if (g_isStartGame) {
			while (g_Pad[0].GetNumBufferringXInputData() < MAX_BUFFERRING) {
				//���̃��[�v�̓Q�[���J�n���ɂ�������Ȃ��͂��B
				g_Pad[0].XInputStateBufferring();
				//�o�b�t�@�����O�������e�𑊎�ɑ���B
				//�p�b�h���𑊎�ɑ���B
				auto LBL = INetworkLogic().GetLBL();
				LBL->RaisePadData();
				g_frameNo++;
				//1�t���[�����Q��B
				Sleep(TIME_ONE_FRAME);
			}
			//�l�b�g���[�N�p�b�h�̃o�b�t�@�����O�B
			while (g_Pad[1].GetNumBufferringXInputData() < MAX_BUFFERRING) {
				//�����͑���Ȃ��Ȃ邱�Ƃ�����͂��Ȃ̂ŁA�Q�[����������\��������B
				NetworkLogic::GetInstance().Update();
				if (g_getNetPadData == false) {
					Sleep(TIME_ONE_FRAME);
				}
				else {
					
					g_getNetPadData = false;
				}
			}
			
			//�o�b�t�@�����O���ꂽ�����g���ăQ�[����i�s������B
			//�܂��V�����p�b�h�����o�b�t�@�����O����B
			g_Pad[0].XInputStateBufferring();
			//�o�b�t�@�����O�������e�𑊎�ɑ���B
			//�p�b�h���𑊎�ɑ���B
			auto LBL = INetworkLogic().GetLBL();
			LBL->RaisePadData();
			//�����ăl�b�g���[�N�p�b�h�B
			NetworkLogic::GetInstance().Update();
			if (g_getNetPadData == true) {
				
				g_getNetPadData = false;
			}
			else {
				//���̃t���[���Ԃɍ���Ȃ������Ƃ��Ă������B�҂��Ȃ��B
				//�l�b�g���[�N�p�b�h�̓o�b�t�@�����O���͊������璙�߂�B
			}
			//�o�b�t�@�����O���ꂽ�������ƂɃp�b�h�����X�V����B
			g_Pad[0].Update(true);
			g_Pad[1].UpdateFromNetPadData();

			g_frameNo++;
		}
		else {
			//�p�b�h�̍X�V
			g_Pad[0].Update(false);
			NetworkLogic::GetInstance().Update();
		}
		
		g_getNetPadData = false;
		//Engine�N���X�Ƃ��ɂ܂Ƃ߂���AtkEngine�ɏ������킹�܂�
		gameObjectManager().Start();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��鏈���̌Ăяo��
		gameObjectManager().ExecuteFromGameThread();
		//�`��I���B
		g_graphicsEngine->EndRender();
		sw.Stop();
		DWORD sleepTime = max(0, TIME_ONE_FRAME - sw.GetElapsedMillisecond());
		Sleep(sleepTime);
	}

	//�l�b�g���[�N����̐ؒf
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect\n");
}