#include "stdafx.h"
#include "ShaderResourceView.h"
#include "StructuredBuffer.h"

namespace myEngine {
	ShaderResourceView::ShaderResourceView()
	{
	}
	ShaderResourceView::~ShaderResourceView()
	{
	}
	/// <summary>
	/// �J��
	/// </summary>
	void ShaderResourceView::Release()
	{
		if (m_srv != nullptr) {
			m_srv->Release();
			m_srv = nullptr;
		}
		//�����ȃf�[�^�t���O
		m_isValid = false;
	}

	bool ShaderResourceView::Create(StructuredBuffer& structuredBuffer)
	{
		//�f�[�^�̉��(������)
		Release();
		//ID3D11�o�b�t�@�[�̎擾
		ID3D11Buffer* pBuf = structuredBuffer.GetBody();
		if (pBuf != nullptr) {
			//�o�b�t�@���\�[�X�̏��
			D3D11_BUFFER_DESC descBuf;
			/*
			�����œn�����l��0�Ŗ��߂Ă����֐��ł�
			�ڍׂɂ��Ă͎Q�l�����ɏ����Ă���̂Ō��Ă�������
			*/
			//���炭�����������ł�
			ZeroMemory(&descBuf, sizeof(descBuf));
			//pBuf�ŏ����������o�b�t�@���\�[�X�̒l�������Ă���H
			pBuf->GetDesc(&descBuf);

			//�V�F�[�_�[���\�[�X�r���[
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			//������
			ZeroMemory(&desc, sizeof(desc));
			//���\�[�X���o�b�t�@�[�ł�����Ă����t���O�����Ă�
			desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			//�ŏ��Ƀr���[�ɓK�p����C���f�b�N�X(���_)�̔ԍ�
			desc.BufferEx.FirstElement = 0;


			desc.Format = DXGI_FORMAT_UNKNOWN;
		}
		return false;
	}
}
