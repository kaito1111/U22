#include "stdafx.h"
#include "Primitive.h"

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

	void Primitive::Draw(RenderContext& rc)
	{
		//���_�o�b�t�@�ݒ�
		rc.IASetVertexBuffer(m_vertexBuffer);
		rc.IASetIndexBuffer(m_indexBuffer);
		//�v���~�e�B�u�g�|���W�[
		rc.IASetPrimitiveToporogy(m_toology);
		//�`��
		rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}

	void Primitive::Draw(RenderContext& rc, int numVertex)
	{
		rc.IASetVertexBuffer(m_vertexBuffer);
		//�g�|���W�[
		rc.IASetPrimitiveToporogy(m_toology);
		//�`��
		rc.Draw(numVertex, 0);
	}
}

