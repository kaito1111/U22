#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	//�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g���쐬
	//�𑜓x��2048*2048
	//�e�N�X�`���̃t�H�[�}�b�g��R�����̂�32bit���������_�^�B
	m_shadowMapRT.Create(
		2048,
		2048,
		DXGI_FORMAT_R32_FLOAT
	);

	m_lightCameraPosition = { -358.0f, 2000.0, 0.0f };
	m_lightCameraTarget = CVector3::Zero();
}

ShadowMap::~ShadowMap()
{
}

//void ShadowMap::Update()
//{
//	//UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
//}

void ShadowMap::UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir)
{
	//���C�g�̕����ɂ���āA���C�g�̏���������߂�B
	CVector3 lightCameraUpAxis;
	//fabsf()�͂�������Βl
	if (fabsf(lightDir.y) > 0.99998f) {
		//�قڐ^��or�^���������Ă���̂ŁA{ 1,0,0 }��������ɂ���B
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		//�^��or�^�������Ă��Ȃ��̂ŁA{ 0,1,0 }��������ɂ���B
		lightCameraUpAxis = CVector3::AxisY();
	}
	//�J�����̏���������肵���̂ŁA���C�g�r���[�s����v�Z
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);

	//���C�g�v���W�F�N�V�����s����쐬����B
	//���z������̉e�𗎂Ƃ������Ȃ�A���s���e�s����쐬����B
	//������w,h��������ƃV���h�E�}�b�v�͈̔͂��ς��I
	m_lightProjMatirx.MakeOrthoProjectionMatrix(
		5000,
		5000,
		0.1f,
		5000.0f
	);
}

void ShadowMap::UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	//���C�g�̕������v�Z
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//���_�ƒ����_�߂���
		//���炭�o�O�Ȃ̂ŃN���b�V��
		std::abort();
	}
	//���K��
	lightDir.Normalize();
	//�e�����Ƃ�����
	UpdateFromLightDirection(m_lightCameraPosition, lightDir);
}

void ShadowMap::UpdateFromLightTarget()
{
	//���C�g�̕������v�Z
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//���_�ƒ����_�߂���
		//���炭�o�O�Ȃ̂ŃN���b�V��
		std::abort();
	}
	//���K��
	lightDir.Normalize();
	//�e�����Ƃ�����
	UpdateFromLightDirection(m_lightCameraPosition, lightDir);
}

void ShadowMap::BiginRender()
{
	//�f�o�R���擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();
	//RTV��DSV�̃o�b�N�A�b�v
	dc->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);

	//�r���[�|�[�g
	viewport = 1;
	//�r���[�|�[�g�̃o�b�N�A�b�v
	dc->RSGetViewports(&viewport, &oldViewports);

}

void ShadowMap::RenderToShadowMap()
{
	auto dc = g_graphicsEngine->GetD3DDeviceContext();
	//�����_�����O�^�[�Q�b�g��؂�ւ��B
	ID3D11RenderTargetView* rts[] = {
		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g
		m_shadowMapRT.GetRenderTargetView()
	};
	//�[�x�X�e���V���r���[�̐ݒ�
	dc->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//�r���[�|�[�g�̐ݒ�
	dc->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//�V���h�E�}�b�v���N���A
	//�P�ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ�
	float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O
	for (auto& caster : m_shadowCasters) {
		//�o�^����Ă���V���h�E�L���X�^�[�̐�������
		//�V���h�E�}�b�v�`��
		caster->Draw(
			m_lightViewMatrix,
			m_lightProjMatirx,
			enRenderMode_CreateShadowMap
		);
	}
	//�L���X�^�[���N���A
	m_shadowCasters.clear();
}

void ShadowMap::EndRender()
{
	//�f�o�C�X�R���e�L�X�g�̎擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

	//���Ƃɖ߂�
	dc->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);

	//�r���[�|�[�g�����Ƃɖ߂�
	dc->RSSetViewports(viewport, &oldViewports);

	//���
	oldDepthStencilView->Release();
	oldRenderTargetView->Release();
}

