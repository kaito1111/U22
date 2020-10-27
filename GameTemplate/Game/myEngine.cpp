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
	int a = 0;
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
	//printf("���[���ɓ���������́A�쐬���s���Ă��܂��B\n");
	NetworkLogic::GetInstance().CreateRoomOrJoin(L"TestRoom");
	//printf("���[���ɓ��ꂵ�܂����B\n");

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

	//�Q�v���C���[���̃p�b�h�̃A�b�v�f�[�g
	//�o�b�t�@�����O�Ƃ����Ă�B
	m_twoP_Pad.Update();

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
	////FPS�̕\���B
	m_font->Begin();
	wchar_t fps[256];
	swprintf_s(fps, L"FPS = %.1f", m_fps);
	//�t�H���g�����o���B
	m_font->Draw(
		fps,
		{
			FRAME_BUFFER_W * 0.49f,
			FRAME_BUFFER_H * 0.5f
		},
		{0.0f,0.0f,0.0f,1.0f},
		0.0f,
		1.0f,
		{1.0f, 1.0f}
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
	//�ꉞ�����Őؒf�E�E�E�@�x���H
	//�l�b�g���[�N����̐ؒf
	NetworkLogic::GetInstance().Disconnect();
	NetworkLogic::GetInstance().GetLBL()->disconnectReturn();
	//printf("disconnect\n");
}
