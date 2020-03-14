#include "stdafx.h"
#include "DebugMan.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//�V���h�E�L���X�^�[�o�^
		g_graphicsEngine->GetShadowMap()->RegistShdowCaster(&m_skinModel);
		//���[���h�s��X�V
		m_skinModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	}

	void DebugMan::Render()
	{
		//�V���h�E�}�b�v�Ƀ����_�����O
		{
			//�f�o�R���擾
			auto dc = g_graphicsEngine->GetD3DDeviceContext();
			//�����_�����O�^�[�Q�b�g���o�b�N�A�b�v
			ID3D11RenderTargetView* oldRenderTargetView;
			ID3D11DepthStencilView* oldDepthStencilView;
			dc->OMGetRenderTargets(
				1,
				&oldRenderTargetView,
				&oldDepthStencilView
			);
			//�r���[�|�[�g�̃o�b�N�A�b�v
			unsigned int viewport = 1;
			D3D11_VIEWPORT oldViewports;
			dc->RSGetViewports(&viewport, &oldViewports);

			//�V���h�E�}�b�v�Ƀ����_�����O
			//���̊֐�������View�؂�ւ��Ă邩��o�b�N�A�b�v�K�v
			g_graphicsEngine->GetShadowMap()->RenderToShadowMap();

			//���Ƃɖ߂�
			dc->OMSetRenderTargets(
				1,
				&oldRenderTargetView,
				oldDepthStencilView
			);
			dc->RSSetViewports(viewport, &oldViewports);
			//���
			oldDepthStencilView->Release();
			oldRenderTargetView->Release();
		}
		//�ʏ탌���_�����O
		{
			m_skinModel.Draw(
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix(),
				0
			);
		}
	}
}