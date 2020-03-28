#include "stdafx.h"
#include "Bloom.h"

namespace myEngine {

	Bloom::Bloom()
	{
		//�e�����_�[�^�[�Q�b�g�̏�����
		InitRenderTarget();
		//�V�F�[�_�[�̏�����
		InitShader();
		//�A���t�@�u�����h�X�e�[�g
		InitAlphaBlendState();
		//�T���v���[�X�e�[�g
		InitSamplerState();
	}

	Bloom::~Bloom()
	{

	}

	void Bloom::InitRenderTarget()
	{
		//�P�x���o�pRT
		//16Bit���������_�o�b�t�@���g�p
		m_luminaceRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);
	}
	
	void Bloom::InitShader()
	{
		//���̂܂܂̒��_�V�F�[�_�[�����[�h
		m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
		//�P�x�𒊏o�������_�V�F�[�_�[�̃��[�h
		m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
		//X�u���[�p�̒��_�V�F�[�_�[
		m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", Shader::EnType::VS);
		//Y�u���[�p�̒��_�V�F�[�_�[
		m_vsYBlur.Load("Aseets/shader/bloom.fx", "VSYBlur", Shader::EnType::VS);
		//�u���[�p�s�N�Z���V�F�[�_�[
		m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", Shader::EnType::PS);
		//�ŏI�����p�s�N�Z���V�F�[�_�[
		m_psFinal.Load("Assets/Shader/bloom.fx", "PSFinal", Shader::EnType::PS);
	}

	void Bloom::InitAlphaBlendState()
	{
		//�f�t�H���g�ݒ�
		CD3D11_DEFAULT defalut;
		//�f�t�H���g�ŏ�����
		CD3D11_BLEND_DESC blendDesc(defalut);
		
		//�f�o�C�X�̎擾
		auto dv = g_graphicsEngine->GetD3DDevice();

		//���𖳌��ɂ���u�����h�X�e�[�g���쐬
		dv->CreateBlendState(&blendDesc, &m_disableBlendState);

		//�ŏI�����p�u�����h�X�e�[�g�̍쐬
		//�ŏI�����͉��Z�����B
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		//�ŏI�����u�����h�X�e�[�g���쐬
		dv->CreateBlendState(&blendDesc, &m_finalBlendState);
	}

	void Bloom::InitSamplerState()
	{
		//�ݒ�
		D3D11_SAMPLER_DESC desc;
		//���Z�b�g
		ZeroMemory(&desc, sizeof(desc));
		//�e�N�X�`���̓\��� UVW�͈͊O��0.0��1.0
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		//�k���A�g��A�T���v�����O�ɐ��`��Ԏg�p
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//�쐬
		g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	}

	void Bloom::Draw()
	{
		////�f�o�R���擾
		//auto dc = g_graphicsEngine->GetD3DDeviceContext();
		////�T���v���[�X�e�[�g�̃Z�b�g
		//dc->PSSetSamplers(0, 1, &m_samplerState);
		//
		////�P�x���o
		//{
		//	//���u�����h�𖳌��̂���
		//	float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
		//	dc->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

		//	//�P�x���o�p�̃����_�[�^�[�Q�b�g�ɕύX ChangeRenderTarget�̈���dc����˂���Ȃ��I�H
		//	g_graphicsEngine->ChangeRenderTarget(dc, &m_luminaceRT, m_luminaceRT.GetViewport());

		//	//�����_�[�^�[�Q�b�g�̃N���A
		//	float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };
		//	m_luminaceRT.ClearRenderTarget(clearColor);

		//	//�V�[�����e�N�X�`���ɁB
		//	auto mainRTTexSRV = g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV();
		//	dc->PSSetShaderResources(0, 1, &mainRTTexSRV);


		//}
	}
}
