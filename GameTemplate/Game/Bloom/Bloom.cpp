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
		//�萔�o�b�t�@�̏�����
		InitConstantBuffer();
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

		//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g
		//���u���[�p���쐬�B
		m_downSamplingRT[0].Create(
			FRAME_BUFFER_W * 0.5f,	//���̉𑜓x�𔼕���
			FRAME_BUFFER_H,
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);

		//�c�u���[
		m_downSamplingRT[1].Create(
			FRAME_BUFFER_W * 0.5f,
			FRAME_BUFFER_H * 0.5f,	//�𑜓x�𔼕���
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
		////Y�u���[�p�̒��_�V�F�[�_�[
		m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", Shader::EnType::VS);
		////�u���[�p�s�N�Z���V�F�[�_�[
		m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", Shader::EnType::PS);
		////�ŏI�����p�s�N�Z���V�F�[�_�[
		m_psFinal.Load("Assets/Shader/bloom.fx", "PSFinal", Shader::EnType::PS);
	}

	void Bloom::InitAlphaBlendState()
	{
		//�f�t�H���g�ݒ�
		CD3D11_DEFAULT defalut;
		//�f�t�H���g�ŏ�����
		CD3D11_BLEND_DESC blendDesc(defalut);
		
		//�f�o�C�X�̎擾
		auto dv = Engine().GetGraphicsEngine().GetD3DDevice();

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

	void Bloom::InitConstantBuffer()
	{
		//www�悭�悭�l������CB�N���X�g����Create�����ł悩������www
		//�o�b�t�@�[�̐ݒ�
		D3D11_BUFFER_DESC desc;
		//0������
		ZeroMemory(&desc, sizeof(desc));
		//�ǂݎ��A�������ݕ��@
		desc.Usage = D3D11_USAGE_DEFAULT;
		//�萔�o�b�t�@�̃T�C�Y�A16�o�C�g�A���C�����g�ɐ؂�グ
		desc.ByteWidth = (((sizeof(SBlurParam) - 1) / 16) + 1) * 16;
		//�萔�o�b�t�@�Ƃ��ăo�C���h
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//CPU�A�N�Z�X���Ȃ�
		desc.CPUAccessFlags = 0;
		//�쐬
		Engine().GetGraphicsEngine().GetD3DDevice()->CreateBuffer(&desc, NULL, &m_blurParamCB);
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
		Engine().GetGraphicsEngine().GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	}

	void Bloom::Update()
	{
		//�d�݂̍X�V
		float total = 0;
		//�d�݂̌v�Z
		//�����̌��ʂ��ꏏ�Ȃ̂ŁA�T���v�����O����e�N�Z���̐��̔�����OK�I
		//�d�݂�8���T���v�����O�e�N�Z��16
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] = expf(-0.5f * (float)(i * i) / m_blurDispersion);
			total += 2.0f * m_blurParam.weights[i];
		}
		
		//�K�i��
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] /= total;
		}

	}

	void Bloom::Draw(PostEffect& postEfferct)
	{
		//�f�o�R���擾
		auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

		//dc->PSGetSamplers(0, 1, &m_samplerState);

		//�o�b�N�A�b�v
		Engine().GetGraphicsEngine().oldTarget();

		//�T���v���[�X�e�[�g�̃Z�b�g
		dc->PSSetSamplers(0, 1, &m_samplerState);
		
		//�K�E�V�A���t�B���^�͏c���u���[����C�ɂ�����
		//�����c�i�t��OK�j�ł�����Ƃ��ꂢ�ɂł�B
		//�P�x���o
		{
			//���u�����h�𖳌��ɂ���
			float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
			dc->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

			//�P�x���o�p�̃����_�[�^�[�Q�b�g�ɕύX ChangeRenderTarget�̈���dc����˂���Ȃ��I�H
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, &m_luminaceRT, m_luminaceRT.GetViewport());

			//�����_�[�^�[�Q�b�g�̃N���A
			float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };
			m_luminaceRT.ClearRenderTarget(clearColor);

			//�V�[�����e�N�X�`���ɁB
			auto mainRTTexSRV = Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV();
			dc->PSSetShaderResources(0, 1, &mainRTTexSRV);

			//�t���X�N���[���`��
			postEfferct.DrawFullScreenQuadPrimitive(m_vs, m_psLuminance);
		}

		//�P�x�𒊏o�����e�N�X�`����X�u���[��������
		{
			//X�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, &m_downSamplingRT[0], m_downSamplingRT[0].GetViewport());

			//�P�x�e�N�X�`����t0���W�X�^�ɐݒ�
			//�P�x�e�N�X�`���̎擾
			auto luminanceTexSRV = m_luminaceRT.GetRenderTargetSRV();
			//���_�V�F�[�_�[�ɃV�F�[�_�[���\�[�X��ݒ�
			dc->VSSetShaderResources(0, 1, &luminanceTexSRV);
			//�s�N�Z���V�F�[�_�[�Ƀ��\�[�X��ݒ�
			dc->PSSetShaderResources(0, 1, &luminanceTexSRV);

			//�萔�o�b�t�@�̍X�V
			//���̒��_�Ԋu
			m_blurParam.offset.x = 16.0f / m_luminaceRT.GetWidth();
			//�c�̒��_�Ԋu
			m_blurParam.offset.y = 0.0f;
			//�X�V
			dc->UpdateSubresource(m_blurParamCB, 0, nullptr, &m_blurParam, 0, 0);
			//�u���[�p�̒萔�o�b�t�@��ݒ�
			dc->PSSetConstantBuffers(0, 1, &m_blurParamCB);

			//�t���X�N���[���`��
			postEfferct.DrawFullScreenQuadPrimitive(m_vsXBlur, m_psBlur);
		}

		//X�u���[���������e�N�X�`���ɁAY�u���[��������B
		{
			//Y�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, &m_downSamplingRT[1], m_downSamplingRT[1].GetViewport());

			//X�u���[���������e�N�X�`����t0���W�X�^�ɐݒ�
			auto xBlurSRV = m_downSamplingRT[0].GetRenderTargetSRV();
			//shader�ݒ�
			dc->VSSetShaderResources(0, 1, &xBlurSRV);
			dc->PSSetShaderResources(0, 1, &xBlurSRV);

			//�萔�o�b�t�@�X�V
			//���_�Ԋu�i�𑜓x��؂�ւ��Ă�C���[�W
			m_blurParam.offset.x = 0.0f;
			m_blurParam.offset.y = 16.0f / m_luminaceRT.GetHeight();
			dc->UpdateSubresource(m_blurParamCB, 0, nullptr, &m_blurParam, 0, 0);

			//�t���X�N���[���`��
			postEfferct.DrawFullScreenQuadPrimitive(m_vsYBlur, m_psBlur);
		}

		//�Ō�ɂڂ������G�����Z�����Ń��C�������_�����O�^�[�Q�b�g�ɍ������ďI���
		{
			//���C�������_�����O�^�[�Q�b�g�ɕύX
			auto mainRT = Engine().GetGraphicsEngine().GetOffScreenRenderTarget();
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, mainRT, mainRT->GetViewport());

			//XY�u���[���������e�N�X�`����t0���W�X�^�ɐݒ�
			auto srv = m_downSamplingRT[1].GetRenderTargetSRV();
			//srv��ݒ�
			dc->PSSetShaderResources(0, 1, &srv);

			//���Z�����p�̃u�����f�B���O�X�e�[�g��ݒ�
			float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
			//�ŏI�����p�u�����h�X�e�[�g���Z�b�g
			dc->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);

			//�t���X�N���[���`��
			postEfferct.DrawFullScreenQuadPrimitive(m_vs, m_psFinal);

			//�u�����h�X�e�[�g�����Ƃɖ߂�
			dc->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
		}
		//�^�[�Q�b�g�����Ƃɖ߂�
		Engine().GetGraphicsEngine().PostRenderTarget();
	}
}
