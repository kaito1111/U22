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
		//null�|�C���^����Ȃ��Ȃ�
		if (pInitData) {
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = pInitData;
		}
	}
}

