#include "stdafx.h"
#include "StructuredBuffer.h"
/// <summary>
/// StructuredBuffer
/// </summary>
/// <remarks>
/// StructuredBuffer::�S�Ă̗v�f�������T�C�Y�����o�b�t�@
/// Buffer::�ꎞ�I�ɕۑ����Ă������߂̂���
/// </remarks>

namespace myEngine {
	StructuredBuffer::StructuredBuffer()
	{
	}
	StructuredBuffer::~StructuredBuffer()
	{
	}
	//�o�b�t�@�̉��
	void StructuredBuffer::Release()
	{
		if (m_sturcturedBuffer != nullptr) {
			m_sturcturedBuffer->Release();
			m_sturcturedBuffer = nullptr;
		}
	}
	//�o�b�t�@�̍쐬
	bool StructuredBuffer::Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc)
	{
		//����������
		Release();
		//�@�\�Ƃ��Ă�bool�^ �Q�l������URL�\���Ƃ��܂��B
		HRESULT hr;
		//���f����null�|�C���^����Ȃ��Ȃ�
		if (pInitData) {
			//�T�u���\�[�X
			D3D11_SUBRESOURCE_DATA InitData;
			//���f���̑���i������
			InitData.pSysMem = pInitData;
			//�G���[���łȂ����̔���(��������S_OK��Ԃ�)
			hr = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_sturcturedBuffer);
		}
		//���f����NULL�Ȃ�
		else {
			//�G���[���łȂ����̔���(��������FAILED��Ԃ�)
			hr = m_pd3dDevice->CreateBuffer(&bufferDesc, NULL, &m_sturcturedBuffer);
		}
		//hr�̒l�����s�Ȃ�
		if (FAILED(hr)) {
			//�����I��
			return false;
		}

		return true;
	}
}

