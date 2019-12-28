/// <summary>
/// ���_�o�b�t�@
/// </summary>

#pragma once

namespace myEngine {
	class VertexBuffer
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		VertexBuffer();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~VertexBuffer();
		/// <summary>
		/// ���_�o�b�t�@�̍쐬
		/// </summary>
		/// <param name="numVertex">���_��</param>
		/// <param name="stride">���_�X�g���C�h</param>
		/// <param name="pSrcVertexBuffer">�\�[�X���_�o�b�t�@</param>
		/// <returns>�����A���s</returns>
		bool Create(int numVertex, int stride, const void* pSrcVertexBuffer);
		/// <summary>
		/// �J��
		/// </summary>
		void Release();
		/// <summary>
		/// ���_�X�g���C�h���擾
		/// </summary>
		int GetStride() const
		{
			return m_stride;
		}
		/// <summary>
		/// ID3D11Buffer���擾
		/// </summary>
		ID3D11Buffer*& GetBody()
		{
			return m_vertexBuffer;
		}
	private:
		ID3D11Buffer*	m_vertexBuffer = nullptr;	//���_�o�b�t�@
		int				m_stride = 0;				//���_�X�g���C�h
	};

}

