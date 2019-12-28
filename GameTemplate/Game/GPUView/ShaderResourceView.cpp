#include "stdafx.h"
#include "ShaderResourceView.h"
#include "GPUBuffer/StructuredBuffer.h"
#include "myEngine.h"

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
	/// <summary>
	/// StructuredBuffer�p��SRV���쐬
	/// </summary>
	/// <param name="structuredBuffer">�X�g���N�`���[�o�b�t�@�[</param>
	/// <returns>�f�[�^���L�����̃t���O</returns>
	/// <remarks>
	/// true�t���O����������SRV���g����悤��
	/// </remarks>
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

			//�V�F�[�_�[���\�[�X�r���[�̏��
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			//������
			ZeroMemory(&desc, sizeof(desc));
			//���\�[�X���o�b�t�@�[�ł�����Ă����t���O�����Ă�
			desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			//�ŏ��Ƀr���[�ɓK�p����C���f�b�N�X(���_)�̔ԍ�
			desc.BufferEx.FirstElement = 0;

			//��Ԃ̏���������
			desc.Format = DXGI_FORMAT_UNKNOWN;
			//����::�o�b�t�@���\�[�X�̗v�f��
			//�E��::�o�b�t�@���\�[�X�̃T�C�Y/�X�g���N�`���[�o�b�t�@�[�̃T�C�Y�H
			desc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

			//hr�ŃG���[���Ȃ����̔��肵�ASRV�̍쐬
			HRESULT hr = graphicsEngine().GetD3DDevice()->CreateShaderResourceView(pBuf, &desc, &m_srv);
			if (FAILED(hr)) {
				//�G���[
				return false;
			}
		}
		//�L���ȃf�[�^�I
		m_isValid = true;
		return true;
	}
	bool ShaderResourceView::CreateFromDDSTextureFromFile(const wchar_t* fileName)
	{
		//������
		Release();
		//��������炭�S��������
		//DirectX...��HRESULT�^������ʂ�
		HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
			graphicsEngine().GetD3DDevice(),	//D3DDevice
			fileName,							//�t�@�C����
			0,									//�T�C�Y
			D3D11_USAGE_DEFAULT,				//CPU��GPU���A�N�Z�X�\���ǂ����̃t���O
			D3D11_BIND_SHADER_RESOURCE,			//�o�C���h�t���O ex���ѕt�����̃t���O
			0,									//�HCPU�A�N�Z�X�񐔁H
			0,									//�H���̑��̃A�N�Z�X�񐔁H misc�����̑�
			false,								//�HSRGB���Ă����J���[�X�y�[�X�g�����ǂ����I�ȓz�H
			nullptr,							//�e�N�X�`���̃|�C���^
			&m_srv								//srv
		);
		if (FAILED(hr)) {
			//�G���[���b�Z�[�W���ł�\��
			return false;
		}
		return true;
	}
}
