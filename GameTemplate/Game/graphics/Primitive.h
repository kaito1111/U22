/// <summary>
/// �v���~�e�B�u
/// </summary>

#pragma once

#include "GPUBuffer/IndexBuffer.h"
#include "GPUBuffer/vertexBuffer.h"

namespace myEngine {
	class Primitive
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Primitive();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Primitive();
		/// <summary>
		/// �v���~�e�B�u�쐬
		/// </summary>
		/// <param name="topologe">�g�|���W�[(�ڑ��`��)</param>
		/// <param name="numVertex">���_�̐�</param>
		/// <param name="vertexStride">���_�X�g���C�h</param>
		/// <param name="pSrcVertexBuffer">�\�[�X�ƂȂ钸�_�o�b�t�@</param>
		/// <param name="numIndex">�C���f�b�N�X�̐�</param>
		/// <param name="indexType">�C���f�b�N�X�̌^</param>
		/// <param name="pSrcIndexBuffer">�\�[�X�ƂȂ�C���f�b�N�X�o�b�t�@</param>
		/// <returns>true:�����@false:���s</returns>
		/// <remarks>
		/// D3D_PRIMITIVE_TOPOLOGY
		///	�o�C���h(���т����ꂽ)���_�f�[�^���ǂ̂悤�ɉ��߂��邩�̒l�������
		/// �ڂ����͎Q�lMemo��
		/// vertexStride
		/// �X�g���C�h �� �z����v�f�̊Ԋu 
		/// �ڂ����͎Q�lMemo��
		/// </remarks>
		bool Create(
			D3D_PRIMITIVE_TOPOLOGY  topologe,
			int numVertex,
			int vertexStride,
			void* pSrcVertexBuffer,
			int numIndex,
			IndexBuffer::EnIndexType indexType,
			void* pSrcIndexBuffer
		);
		/// <summary>
		/// �����I�ɊJ��
		/// </summary>
		void Release();
		/// <summary>
		/// �o�[�e�b�N�X�o�b�t�@�̕`��
		/// </summary>
		void Draw(ID3D11DeviceContext& dc, int numVertex);
		/// <summary>
		/// �C���f�b�N�X�o�b�t�@�̕`��
		/// </summary>
		/// <param name="dc"></param>
		/// <param name="numVertex"></param>
		void Draw(ID3D11DeviceContext& dc);
		/// <summary>
		/// ���_�o�b�t�@�̎擾
		/// </summary>
		/// <returns>���_�o�b�t�@</returns>
		VertexBuffer& GetVertexBuffer()
		{
			return m_vertexBuffer;
		}
	private:
		VertexBuffer			m_vertexBuffer;		//���_�o�b�t�@
		IndexBuffer				m_indexBuffer;		//�C���f�b�N�X�o�b�t�@
		D3D_PRIMITIVE_TOPOLOGY	m_toology;			//�g�|���W�[
	};
}


