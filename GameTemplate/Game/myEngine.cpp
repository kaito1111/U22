#include "stdafx.h"
#include "myEngine.h"
#include "util/tkStopwatch.h"
#include "Network/NetworkLogic.h"
#include "system/system.h"

CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::Init()
{
	//�Q�[���̏�����
	InitGame();
	//�l�b�g���[�N�̏������֘A���� 
	//�l�b�g���[�N�̓G���W�����̏����H����Ƃ��Ⴄ�����ŁA�������ׂ��H�H
	NetworkLogic::GetInstance().Start();
}

bool CEngine::Start()
{
	//���[���ɓ���
	printf("���[���ɓ���������́A�쐬���s���Ă��܂��B\n");
	NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	printf("���[���ɓ��ꂵ�܂����B\n");

	//�t�H���g�쐬�B
	m_font = std::make_unique<CFont>();

	return true;
}

void CEngine::Update()
{
	//�X�^�[�g
	m_sw.Start();
	//�`��J�n�B
	Engine().GetGraphicsEngine().BegineRender();
	//�����G���W���̍X�V�B
	g_physics.Update();
	//�T�E���h�G���W���̍X�V
	Engine().GetSoundEngine().Update();
	//�J�����X�V�B
	g_camera3D.Update();
	g_camera2D.Update2D();

	//�l�b�g���[�N�̍X�V
	//���̃p�b�h�̃o�b�t�@�����O�����APlayer2�̃p�b�h�֘A������
	//twoP_Pad�ŏ����ׂ��B
	if (INetworkLogic().GetLBL()->GetReady()) {
		//�Q�[�����J�n����Ă���
		while (g_Pad[0].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//���̃��[�v�̓Q�[���J�n���ɂ�������Ȃ��͂��B
			g_Pad[0].XInputStateBufferring();
			//�o�b�t�@�����O�������e�𑊎�ɑ���B
			//�p�b�h���𑊎�ɑ���B
			LBLobj()->RaisePadData();
			m_frameNo++;
			//1�t���[�����Q��B
			Sleep(TIME_ONE_FRAME);
		}
		//�l�b�g���[�N�p�b�h�̃o�b�t�@�����O�B
		while (g_Pad[1].GetNumBufferringXInputData() < MAX_BUFFERRING) {
			//�����͑���Ȃ��Ȃ邱�Ƃ�����͂��Ȃ̂ŁA�Q�[����������\��������B
			NetworkLogic::GetInstance().Update();
			if (LBLobj()->getReceiveFlag() == false) {
				//�܂��l�b�g���[�N�p�b�h�̃f�[�^����M�ł��Ă��Ȃ��B
				//1�t���[���ҋ@�B
				Sleep(TIME_ONE_FRAME);
			}
			else {
				//�l�b�g���[�N�p�b�h�̃f�[�^����M�����B
				LBLobj()->SetReceiveFlag(false);
			}
		}

		//�o�b�t�@�����O���ꂽ�����g���ăQ�[����i�s������B
		//�܂��V�����p�b�h�����o�b�t�@�����O����B
		g_Pad[0].XInputStateBufferring();
		//�o�b�t�@�����O�������e�𑊎�ɑ���B
		//�p�b�h���𑊎�ɑ���B
		LBLobj()->RaisePadData();
		//�����ăl�b�g���[�N�p�b�h�B
		NetworkLogic::GetInstance().Update();
		if (LBLobj()->getReceiveFlag() == true) {
			LBLobj()->SetReceiveFlag(false);
		}
		else {
			//���̃t���[���Ԃɍ���Ȃ������Ƃ��Ă������B�҂��Ȃ��B
			//�l�b�g���[�N�p�b�h�̓o�b�t�@�����O���͊������璙�߂�B
		}
		printf("Pad::Update Start\n");
		//�o�b�t�@�����O���ꂽ�������ƂɃp�b�h�����X�V����B
		g_Pad[0].Update(true);
		g_Pad[1].UpdateFromNetPadData();
		printf("Pad::Update End\n");
		m_frameNo++;
	}
	else {
		//�p�b�h�̍X�V
		//�Q�[�����J�n����Ă��Ȃ��B
		g_Pad[0].Update(false);
		NetworkLogic::GetInstance().Update();
	}

	LBLobj()->SetReceiveFlag(false);
	//Engine�N���X�Ƃ��ɂ܂Ƃ߂���AtkEngine�ɏ������킹�܂�
	gameObjectManager().Start();
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ł��鏈���̌Ăяo��
	gameObjectManager().ExecuteFromGameThread();
	//30�t���[��
	static int count = 0;
	m_timeTotal += (float)m_sw.GetElapsed();
	count++;
	if (count == 30) {
		//����v�Z����Əd���̂��ȁH
		//30�t���[�����̕���FPS�̌v�Z
		m_fps = 1.0f / (m_timeTotal / count);
		m_timeTotal = 0.0f;
		count = 0;
	}
	//FPS�̕\���B
	m_font->Begin();
	wchar_t fps[256];
	swprintf_s(fps, L"FPS = %.1f", m_fps);
	//�t�H���g�����o���B
	m_font->Draw(
		fps,
		{
			FRAME_BUFFER_W * -0.18f,
			FRAME_BUFFER_H 
		},
		{0.0f,0.0f,0.0f,1.0f},
		0.0f,
		1.0f,
		{0.0f, 1.0f}
	);
	m_font->End();
	//�`��I���B
	Engine().GetGraphicsEngine().EndRender();
	DWORD sleepTime = max(0, TIME_ONE_FRAME - m_sw.GetElapsedMillisecond());
	Sleep(sleepTime);
	//�X�g�b�v
	m_sw.Stop();
}

void CEngine::Final()
{
	//�l�b�g���[�N����̐ؒf
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	printf("disconnect\n");
}
