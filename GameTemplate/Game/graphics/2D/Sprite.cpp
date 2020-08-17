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
	/// SSimpleVertex��2D������l�p�`�̏�����
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
		//UVW��1�𒴂���Ƃ��̃e�N�X�`���̏������ǂ����邩
		//D3D11_TEXTURE_ADDRESS_WRAP�͕��ʂɌJ��Ԃ��@�⑫...�~���[�Ƃ�����������
		dese.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		//�k���A�g��A�T���v�����O�ɐ��`��Ԃ��g�p
		dese.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//�T���v���[�X�e�[�g�̍쐬����
		//������Sprite�N���X�̃T���v���[�X�e�[�g�Ƀ|�C���^�������I
		Engine().GetGraphicsEngine().GetD3DDevice()->CreateSamplerState(&dese, &SamplerState);


		//�u�����h�X�e�[�g�̐ݒ�
		CD3D11_DEFAULT drfault;
		CD3D11_BLEND_DESC BLEND_DETE(drfault);
		BLEND_DETE.RenderTarget[0].BlendEnable = true;
		BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		
		//�u�����h�X�e�[�g�̍쐬 & ������
		auto Device = Engine().GetGraphicsEngine().GetD3DDevice();
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

	void Sprite::Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix, const float w)
	{
		
		//CMatrix view;
		//CMatrix proj;
		//view.MakeLookAt(
		//	{ 0.0f,0.0f,-1.0f },
		//	{ 0.0f,0.0f,0.0f },
		//	CVector3::Up()
		//);

		//proj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 2.0f);

		ID3D11DeviceContext* d3dDeviceContext = Engine().GetGraphicsEngine().GetD3DDeviceContext();

		/*
		if (m_isInited == false) {
			//��������
			return;
		}
		*/
		if (m_textureSRV == nullptr) {
			//SRV���Ȃ�
			//SRV�̃|�C���^�m�F���Ă�
			throw;
			return;
		}
		//�萔�o�b�t�@
		SSpriteCB cb;
		//�v���W�F�N�V�����s�����Z
		cb.WVP = m_world;
		cb.WVP = cb.WVP * viewMatrix;
		cb.WVP = cb.WVP * projMatrix;
		//��Z�J���[�̑�� + �����x�̏�Z
		cb.m_mulColor = m_mulColor * w;

		d3dDeviceContext->UpdateSubresource(m_cb.GetBody(), 0, NULL, &cb, 0, 0);

		d3dDeviceContext->VSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb.GetBody());
		d3dDeviceContext->PSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb.GetBody());
		d3dDeviceContext->VSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
		d3dDeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
		d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());

		//�T���v���[�X�e�[�g�̃Z�b�g
		Engine().GetGraphicsEngine().GetD3DDeviceContext()->VSSetSamplers(0, 1, &SamplerState);
		Engine().GetGraphicsEngine().GetD3DDeviceContext()->PSSetSamplers(0, 1, &SamplerState);

		m_primitive.Draw(*d3dDeviceContext);
	}
}