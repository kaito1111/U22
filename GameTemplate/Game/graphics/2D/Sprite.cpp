#include "stdafx.h"
#include "Sprite.h"
#include "GPUView/ShaderResourceView.h"
#include "graphics/Shader.h"
#include "math/Matrix.h"

namespace myEngine {
	struct SSimpleVertex
	{
		CVector4 pos;
		CVector2 tex;
	};
	//�s�{�b�g�̏�����
	const CVector2 Sprite::DEFAULT_PIVOT = { 0.5f,0.5f };
	Sprite::Sprite()
	{
	}
	Sprite::~Sprite()
	{
	}
	/// <summary>
	/// SRV�̃��[�h
	/// </summary>
	/// <remarks>
	/// SSimpleVertex��2D������l�p�`�̏������H
	/// </remarks>
	void Sprite::Init(ID3D11ShaderResourceView* tex, float w, float h)
	{
		//�V�F�[�_�[�����[�h
		m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
		m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//�傫��
		m_size.x = w / 1280.0f;
		m_size.y = h / 720.0f;
		float halfW = w * 0.5f;
		float halfH = h * 0.5f;
		//���_�o�b�t�@�̃\�[�X�f�[�^
		SSimpleVertex vertices[] =
		{
			{
				CVector4(-halfW, -halfH, 0.0f, 1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(halfW, -halfH, 0.0f, 1.0f),
				CVector2(1.0f, 1.0f),
			},
			{
				CVector4(-halfW, halfH, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(halfW, halfH, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}
		};
		short indices[] = { 0,1,2,3 };
		//�v���~�e�B�u�̍쐬
		m_primitive.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			IndexBuffer::enIndexType_16,
			indices
		);

		//�����œ����Ă����e�N�X�`���̑��
		m_textureSRV = tex;
		//�萔�o�b�t�@�̍쐬
		m_cb.Create(nullptr, sizeof(SSpriteCB));
		
		//�T���v���[�X�e�[�g�̍쐬
		D3D11_SAMPLER_DESC dese;
		//�T���v���[�X�e�[�g�֘A�̏���������
		ZeroMemory(&dese, sizeof(dese));
		dese.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//�T���v���[�X�e�[�g�̍쐬����
		//������Sprite�N���X�̃T���v���[�X�e�[�g�Ƀ|�C���^�������I
		g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&dese, &SamplerState);


		//�u�����h�X�e�[�g�̐ݒ�
		CD3D11_DEFAULT drfault;
		CD3D11_BLEND_DESC BLEND_DETE(drfault);
		BLEND_DETE.RenderTarget[0].BlendEnable = true;
		//2�����ŏ��������Ă�� �����l�Ȃ̂łł���I
		BLEND_DETE.RenderTarget[0].BlendOp = BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].DestBlend = BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].SrcBlend = BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;

		//�u�����h�X�e�[�g�̍쐬 & ������
		auto Device = g_graphicsEngine->GetD3DDevice(); 
		Device->CreateBlendState(&BLEND_DETE, &BlendState);
	}
	void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
	{
		//if (m_isInited == false) {
		//	//����������ĂȂ�
		//	return;
		//}
		//�s�{�b�g���l���ɓ��ꂽ���s�ړ��s����쐬
		//�s�{�b�g�͐^�񒆂�0,0,0�A���オ-1,-1�A�E����1.0,1.0�ɂȂ�悤��
		CVector2 localPivot = pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//�摜�̃n�[�t�T�C�Y�����߂�
		CVector2 halfSize = m_size;
		halfSize.x *= 0.5f;
		halfSize.y *= 0.5f;
		CMatrix mPivotTrans;

		mPivotTrans.MakeTranslation(
			{halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f}
		);
		CMatrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(trans);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		m_world = mPivotTrans * mScale;
		m_world = m_world * mRot;
		m_world = m_world * mTrans;
	}

	void Sprite::Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{

		CMatrix view;
		CMatrix proj;
		view.MakeLookAt(
			{ 0.0f,0.0f,-1.0f },
			{ 0.0f,0.0f,0.0f },
			CVector3::Up()
		);

		proj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 2.0f);

		ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		/*
		g_graphicsEngine->GetD3DDeviceContext()->OMSetBlendState(kjl, nullptr, 0xFFFFFFFF);
		MemoryBarrier();
		
		ID3D11DepthStencilState* kkkkk;
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		desc.StencilEnable = false;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		pd3d->CreateDepthStencilState(&desc, &kkkkk);

		g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(kkkkk, 0);
		*/
		/*
		if (m_isInited == false) {
			//��������
			return;
		}
		*/
		if (m_textureSRV == nullptr) {
			//SRV���Ȃ�
			//tkEngine�͂����ŃG���[���b�Z�[�W
			return;
		}
		//�萔�o�b�t�@
		SSpriteCB cb;
		//�v���W�F�N�V�����s�����Z
		cb.WVP = m_world;
		cb.WVP = cb.WVP * view;
		cb.WVP = cb.WVP * proj;
		//��Z�J���[�̑��
		cb.m_mulColor = m_mulColor;

		d3dDeviceContext->UpdateSubresource(m_cb.GetBody(), 0, NULL, &cb, 0, 0);
		d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb.GetBody());
		d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb.GetBody());
		d3dDeviceContext->VSSetShaderResources(0, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShaderResources(0, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
		d3dDeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
		d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());
		//rc.UpdateSubResourse(m_cb, &cb);
		//rc.VSSetConstantBuffer(0, m_cb);
		//rc.PSSetConstantBuffer(0, m_cb);
		//g_graphicsEngine->GetD3DDeviceContext()->VSSetShaderResources(0, 1, &m_textureSRV->GetBody());
		//g_graphicsEngine->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_textureSRV->GetBody());
		////rc.PSSetShaderResource(0, *m_textureSRV);
		//rc.PSSetShader(m_ps);
		//rc.VSSetShader(m_vs);

		//g_graphicsEngine->GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
		g_graphicsEngine->GetD3DDeviceContext()->VSSetSamplers(0, 1, &SamplerState);
		g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers(0, 1, &SamplerState);

		//ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//g_graphicsEngine->GetD3DDeviceContext()->OMSetBlendState(kjl, nullptr, 0xFFFFFFFF);

		m_primitive.Draw(*d3dDeviceContext);
	}
}