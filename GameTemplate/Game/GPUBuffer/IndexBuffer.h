/// <summary>
/// �C���f�b�N�X�o�b�t�@
/// </summary>
/// <remarks>
/// �H�H�C���f�b�N�X�o�b�t�@�H�H
///	���Ԃ��Ă钸�_�Ƃ�����Ȃ��̂Ŗ��ʂ��Ȃ��������Ă����o�b�t�@
/// </remarks>

#pragma once

namespace myEngine {
	class IndexBuffer
	{
	public:
		/// <summary>
		/// �C���f�b�N�X�̌^
		/// </summary>
		/// <remarks>
		/// �񋓌^
		/// </remarks>
		enum EnIndexType {
			enIndexType_16,		//16�r�b�g�̃C���f�b�N�X
			enIndexType_32,		//32�r�b�g�̃C���f�b�N�X
		};
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		IndexBuffer();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~IndexBuffer();
		/// <summary>
		/// �C���f�b�N�X�o�b�t�@�쐬
		/// </summary>
		/// <param name="numIndex">�C���f�b�N�X�̐�</param>
		/// <param name="indexType">�C���f�b�N�X�̌^</param>
		/// <param name="pSrcIndexBuffer">�\�[�X�C���f�b�N�X�o�b�t�@</param>
		/// <returns></returns>
		bool Create(int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer);
		/// <summary>
		/// �J������
		/// <para>�����I�ȃ^�C�~���O�ŊJ������ꍇ�Ă�</para>
		/// </summary>
		void Release();
		/// <summary>
		/// �C���f�b�N�X�̌^���擾
		/// </summary>
		/// <returns>�C���f�b�N�X�̌^</returns>
		EnIndexType GetIndexType() const
		{
			return m_indexType;
		}
		/// <summary>
		/// �C���f�b�N�X�o�b�t�@�̎擾
		/// </summary>
		/// <returns>�C���f�b�N�X</returns>
		ID3D11Buffer* GetBody() const
		{
			return m_indexBuffer;
		}
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		unsigned int GetNumIndex() const
		{
			return m_numIndex;
		}
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool IsCreated() const
		{
			return m_isCreated;
		}
	private:
		bool			m_isCreated = false;			//�C���f�b�N�X�o�b�t�@�쐬����Ă�H
		ID3D11Buffer*	m_indexBuffer = nullptr;		//�C���f�b�N�X�o�b�t�@
		EnIndexType		m_indexType = enIndexType_16;	//�C���f�b�N�X�o�b�t�@�̌^
		unsigned int	m_numIndex = 0;					//�C���f�b�N�X�o�b�t�@�̐�
	};
}


