#include "stdafx.h"
#include "ConstantBuffer.h"

namespace myEngine {
	ConstantBuffer::ConstantBuffer()
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::Create(const void* pInitData, int bufferSize)
	{
		//�萔�o�b�t�@�p�̃o�b�t�@��`
		D3D11_BUFFER_DESC bufferDesc;
		//�o�b�t�@��`�̏�����
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		//�A�N�Z�X�t���O���f�t�H���g
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//16�o�C�g�A���C�����g�ɐ؂�グ���Q�lURL
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
		//�萔�o�b�t�@�Ƃ��Č��ѕt��
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		return GPUBuffer::Create(pInitData, bufferDesc);
	}
}

