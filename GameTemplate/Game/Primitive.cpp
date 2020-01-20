#include "stdafx.h"
#include "Primitive.h"
#include "GPUBuffer/IndexBuffer.h"

namespace myEngine {
	Primitive::Primitive()
	{
	}
	Primitive::~Primitive()
	{
		Release();
	}
	//�J��
	void Primitive::Release()
	{
		m_vertexBuffer.Release();
		m_indexBuffer.Release();
	}
	//�v���~�e�B�u�̍쐬
	bool Primitive::Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		IndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer
	)
	{
		//������
		Release();
		//�ڑ��`��
		m_toology = topology;
		//���_�o�b�t�@�̍쐬�ƃG���[���o
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
		if (!result) {
			//�G���[
			return false;
		}
		if (pSrcIndexBuffer) {
			//�C���f�b�N�X�쐬�ƃG���[���o
			result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
			if (!result) {
				//�G���[
				return false;
			}
		}
		//����
		return true;
	}

	//void Primitive::Draw(RenderContext& rc)
	//{
	//	//���_�o�b�t�@�ݒ�
	//	rc.IASetVertexBuffer(m_vertexBuffer);
	//	rc.IASetIndexBuffer(m_indexBuffer);
	//	//�v���~�e�B�u�g�|���W�[
	//	rc.IASetPrimitiveToporogy(m_toology);
	//	//�`��
	//	rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	//}

	void Primitive::Draw(ID3D11DeviceContext& dc)
	{
		UINT ofset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		dc.IASetVertexBuffers(0, 1, &m_vertexBuffer.GetBody(), &stride, &ofset);
		auto type = m_indexBuffer.GetIndexType();
		dc.IASetIndexBuffer(
			m_indexBuffer.GetBody(),
			type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
			0
		);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�B
		dc.IASetPrimitiveTopology(m_toology);
		//�`��B
		dc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}

	void Primitive::Draw(ID3D11DeviceContext& rc, int numVertex)
	{
		//���_�o�b�t�@��ݒ�B
		UINT ofset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		rc.IASetVertexBuffers(0, 1, &(m_vertexBuffer.GetBody()), &stride, &ofset);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�B
		rc.IASetPrimitiveTopology(m_toology);
		//�`��B
		rc.Draw(numVertex, 0);
	}
}

