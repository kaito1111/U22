#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Release()
{
	//�����_�[�^�[�Q�b�g�̉��
	if (m_renderTargetTex != nullptr)
	{
		m_renderTargetTex->Release();
	}
	//�����_�[�^�[�Q�b�g�r���[�̉��
	if (m_renderTargetView != nullptr)
	{
		m_renderTargetView->Release();
	}
	//�����_�[�^�[�Q�b�gSRV�̉��
	if (m_renderTargetSRV != nullptr)
	{
		m_renderTargetSRV->Release();
	}
	//�f�v�X�X�e���V���e�N�X�`�����̉��
	if (m_depthStencilTex != nullptr)
	{
		m_depthStencilTex->Release();
	}
	//�f�v�X�X�e���V���r���[
	if (m_depthStencilView != nullptr)
	{
		m_depthStencilView->Release();
	}
}

void RenderTarget::Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat)
{
	//�f�o�C�X�擾
	auto dv = g_graphicsEngine->GetD3DDevice();

	//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���쐬
	D3D11_TEXTURE2D_DESC texDesc = { 0 };
	{
		//�e�N�X�`���̍쐬

		//�e�N�X�`���̉��̉𑜓x
		texDesc.Width = w;
		//�e�N�X�`���̏c�̉𑜓x
		texDesc.Height = h;
		//�~�j�}�b�v���x��
		texDesc.MipLevels = 1;
		//�e�N�X�`���̔z��T�C�Y
		texDesc.ArraySize = 1;
		//�e�N�X�`���̃t�H�[�}�b�g
		//RGBA�̊e�v�f8Bit��32Bit�t�H�[�}�b�g
		texDesc.Format = texFormat;
		//�e�N�X�`���̎g�p�p�r�����߂�
		//�����_�����O�^�[�Q�b�g�̃e�N�X�`����
		//�����_�����O�^�[�Q�b�g�AShaderResourceView, UnorderedAccessView�Ƃ��ăo�C���h
		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		//�}���`�T���v�����O�̐�
		texDesc.SampleDesc.Count = 1;
		//�}���`�T���v�����O�̕i��
		texDesc.SampleDesc.Quality = 0;
		//�e�N�X�`���̓ǂݏ����̂����
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		//CPU����̃A�N�Z�X�̎d��
		texDesc.CPUAccessFlags = 0;
		//0
		texDesc.MiscFlags = 0;
		//�e�N�X�`���쐬
		dv->CreateTexture2D(&texDesc, nullptr, &m_renderTargetTex);
	}

	//�����_�����O�^�[�Q�b�g�r���[�̍쐬
	{
		//�����_�����O�^�[�Q�b�g�r���[�̍쐬

		//�����_�����O�^�[�Q�b�g�r���[���쐬���邽�߂̃f�[�^�ݒ�
		D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
		//�t�H�[�}�b�g�̓e�N�X�`���Ɠ���
		viewDesc.Format = texDesc.Format;
		//2D�e�N�X�`�����������Ƃ��w��
		viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		//0
		viewDesc.Texture2D.MipSlice = 0;
		//�����_�����O�^�[�Q�b�g�r���[�̍쐬
		dv->CreateRenderTargetView(m_renderTargetTex, &viewDesc, &m_renderTargetView);
	}

	{

		//////////////////////////////////////////////////////////////
		//��������V�F�[�_�[���\�[�X�r���[�̍쐬�B
		//////////////////////////////////////////////////////////////

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		//�t�H�[�}�b�g�̓e�N�X�`���Ɠ����ł悢�B
		srvDesc.Format = texDesc.Format;
		//2�����e�N�X�`���Ƃ��Ĉ����B
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		//�~�b�v�}�b�v���x�����e�N�X�`���Ɠ����ł悢�B
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
		//0�ł����B
		srvDesc.Texture2D.MostDetailedMip = 0;
		//SRV���쐬����B
		dv->CreateShaderResourceView(m_renderTargetTex, &srvDesc, &m_renderTargetSRV);
	}
	//4.�f�v�X�X�e���V���e�N�X�`���̍쐬
	D3D11_TEXTURE2D_DESC depthTexDesc = texDesc;
	{
		//////////////////////////////////////////////////////////////
		//��������f�v�X�X�e���V���e�N�X�`���̍쐬�B
		//////////////////////////////////////////////////////////////
		//�f�v�X�X�e���V���r���[�Ƀo�C���h����B
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//32bit���������_�̃f�v�X�X�e���V���o�b�t�@���쐬����B
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//�f�v�X�X�e���V���e�N�X�`�����쐬����B
		dv->CreateTexture2D(&depthTexDesc, nullptr, &m_depthStencilTex);
	}
	//5.�f�v�X�X�e���V���r���[�̍쐬
	{
		//////////////////////////////////////////////////////////////
		//��������f�v�X�X�e���V���r���[�̍쐬�B
		//////////////////////////////////////////////////////////////
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		//�t�H�[�}�b�g�͐[�x�X�e���V���Ɠ����ɂ���B
		depthStencilViewDesc.Format = depthTexDesc.Format;
		//2D�e�N�X�`�����������Ƃ��w�肷��B
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//0�ł����B
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		//0�ł����B
		depthStencilViewDesc.Flags = 0;
		//�f�v�X�X�e���V���r���[���쐬�B
		dv->CreateDepthStencilView(m_depthStencilTex, &depthStencilViewDesc, &m_depthStencilView);
	}
}

void RenderTarget::ClearRenderTarget(float* clearColor)
{
	//�f�o�C�X�擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

	//�N���A
	dc->ClearRenderTargetView(m_renderTargetView, clearColor);
	dc->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}