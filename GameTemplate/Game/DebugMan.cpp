#include "stdafx.h"
#include "DebugMan.h"
#include "Stage.h"

namespace myEngine {

	DebugMan::DebugMan()
	{
		//�S�[���̈ʒu
		//m_pos = { -358.0f,925.0f,0.0f };
		m_pos = CVector3::Zero();
		m_skinModel.Init(L"Assets/modelData/unityChan.cmo");
		//�e�𗎂Ƃ��J�����̍��W
		m_lightCameraPosition = { 0.0f, 0.0f, -50.0f };
		//�e�𗎂Ƃ������_�̍��W
		m_lightCameraTarget = m_pos;/*CVector3::Zero();*/
	}

	DebugMan::~DebugMan()
	{

	}

	void DebugMan::Update()
	{
		//�V���h�E�L���X�^�[�o�^
		g_graphicsEngine->GetShadowMap()->RegistShdowCaster(&m_skinModel);
		//���C�g�̍��W���X�V
		g_graphicsEngine->GetShadowMap()->UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
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
			//���̊֐�������TargetView�؂�ւ��Ă邩��o�b�N�A�b�v�K�v
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
	}



	void DebugMan::Draw()
	{
		//�ʏ탌���_�����O
		{
			m_skinModel.Draw(
				g_camera3D.GetViewMatrix(),
				g_camera3D.GetProjectionMatrix(),
				0,
				g_graphicsEngine->GetShadowMap()->GetLightViewMatirx(),
				g_graphicsEngine->GetShadowMap()->GetLightProjMatirx()
			);
		}
	}
}