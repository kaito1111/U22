#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "exampleCode/ex2D.h"
#include "KaitoTask.h"
#include "DebugMan.h"
#include "GameCamera.h"

Game::Game()
{
	//�T�E���h�̏�����
	m_se.Init(L"Assets/sound/coinGet.wav");

	//���C���ƂȂ郌���_�[�^�[�Q�b�g�̃N���G�C�g
	//m_mainRenderTarget.Create(
	//	FRAME_BUFFER_W,
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R8G8B8A8_UNORM
	//);

	//���C�������_�[�^�[�Q�b�g�ɂ����ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂ɃX�v���C�g��������
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

}

Game::~Game()
{
	//���
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
}

bool Game::Start()
{
	//1�Ԗ�
	NewGO< KaitoTask>(5, "kaito");
	//2�Ԗ�
	Stage* stage = NewGO<Stage>(0, "stage");
	//NewGO<DirectionLight>(3, "light");
	effect = NewGO<Effect>(1);

	return true;
}

void Game::Update()
{
	Sample();
}

//���낢��ȃT���v��
void Game::Sample()
{
	if (GetAsyncKeyState('H'))
	{
		//2D�̃T���v��
		//ex2D* ex2d = NewGO<ex2D>(4, "ex2D");
		
		//�f�o�b�O�pUnitychan��NewGO
		NewGO<DebugMan>(0, "debugman");

		//�G�t�F�N�g�̍쐬
		if (!effect->IsPlay()) {
			effect = NewGO<Effect>(1);
			effect->Play(L"Assets/effect/test.efk");
			effect->SetPosition({ 100,0, 0 });
			effect->SetScale(CVector3::One() * 20);
		}
		//�T�E���h�̍Đ�
		m_se.Play(false);
	}
}

void Game::Draw()
{
	//auto dc = g_graphicsEngine->GetD3DDeviceContext();

	////�o�b�N�A�b�v�̏���
	//{
	//	//�����_�[�^�[�Q�b�g�̃o�b�N�A�b�v
	//	dc->OMGetRenderTargets(
	//		1,
	//		&m_frameBufferRenderTargetView,
	//		&m_frameBufferDepthStencilView
	//	);
	//	//�r���[�|�[�g�o�b�N�A�b�v
	//	unsigned int numViewport = 1;
	//	dc->RSGetViewports(&numViewport, &m_frameBufferViewports);
	//}

	////�����_�[�^�[�Q�b�g���Z�b�g
	//g_graphicsEngine->ChangeRenderTarget(dc, &m_mainRenderTarget, &m_frameBufferViewports);

	////���C�������_�����O�^�[�Q�b�g���N���A
	//float clearColor[] = { 0.5f,0.5f,0.5f,1.0f };
	//m_mainRenderTarget.ClearRenderTarget(clearColor);

	//~Draw����
}

void Game::PostRender()
{
	//auto dc = g_graphicsEngine->GetD3DDeviceContext();

	////�^�[�Q�b�g���t���[���o�b�t�@��
	//g_graphicsEngine->ChangeRenderTarget(
	//	dc, 
	//	m_frameBufferRenderTargetView, 
	//	m_frameBufferDepthStencilView, 
	//	&m_frameBufferViewports
	//);
	////�N���A
	//
	//dc->ClearDepthStencilView(m_frameBufferDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	//CQuaternion qRot = CQuaternion::Identity();
	////qRot.SetRotationDeg(CVector3::AxisY(), 180);

	////�h���[
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);

	//m_frameBufferRenderTargetView->Release();
	//m_frameBufferDepthStencilView->Release();
}