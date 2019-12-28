#include "stdafx.h"
#include "IndexBuffer.h"
#include "myEngine.h"

namespace myEngine {
	IndexBuffer::IndexBuffer()
	{
	}
	IndexBuffer::~IndexBuffer()
	{
		//�J��
		Release();
	}
	void IndexBuffer::Release()
	{
		if (m_indexBuffer) {
			m_indexBuffer->Release();
			m_indexBuffer = nullptr;
		}
		m_isCreated = false;
	}
	bool IndexBuffer::Create(int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer)
	{
		//������
		Release();

		int stride = 0;
		if (indexType == enIndexType_16) {
			//16bit�Ȃ�
			stride = 2;
		}
		else {
			//32bit�Ȃ�
			stride = 4;
		}
		//�C���f�b�N�X�^�C�v
		m_indexType = indexType;
		//�C���f�b�N�X�̐�
		m_numIndex = numIndex;
		//�o�b�t�@���\�[�X
		D3D11_BUFFER_DESC bd;
		//bd�̃|�C���^��������
		ZeroMemory(&bd, sizeof(bd));
		//GPU�A�N�Z�X�t���O���f�t�H���g��
		bd.Usage = D3D11_USAGE_DEFAULT;
		//�X�g���N�`���o�b�t�@�̃T�C�Y
		bd.StructureByteStride = stride;
		//�C���f�b�N�X�o�b�t�@�̃T�C�Y
		bd.ByteWidth = stride * numIndex;
		//�C���f�b�N�X�o�b�t�@�t���O
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//�悭�킩���t���O
		bd.CPUAccessFlags = 0;
		
		//�T�u���\�[�X(�e�N�X�`���Ƃ��H)
		D3D11_SUBRESOURCE_DATA InitData;
		//�T�u���\�[�X�̏�����
		ZeroMemory(&InitData, sizeof(InitData));
		//�\�[�X�C���f�b�N�X�o�b�t�@�̑�� pSysMem���������|�C���^
		InitData.pSysMem = pSrcIndexBuffer;

		//�G���[���o����Create
		HRESULT hr = graphicsEngine().GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
		if (FAILED(hr)) {
			//���s
			return false;
		}
		//����
		m_isCreated = true;
		return true;
	}
}

