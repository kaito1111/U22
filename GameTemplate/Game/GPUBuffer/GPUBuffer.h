/// <summary>
/// GPU�o�b�t�@�N���X
/// </summary>
/// <remarks>
/// ���N���X
/// </remarks>

#pragma once

namespace myEngine {
	class GPUBuffer
	{
	public:
		GPUBuffer();
		virtual ~GPUBuffer();
		/// <summary>
		/// GPUBuffer�̍쐬
		/// </summary>
		/// <param name="pInitData">�����f�[�^</param>
		/// <param name="bufferDesc">�o�b�t�@��`</param>
		/// <returns>�����A���s</returns>
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/// <summary>
		/// ID3D11Buffer�̎擾
		/// </summary>
		/// <returns>ID3D11Buffer</returns>
		ID3D11Buffer*& GetBody()
		{
			return m_gpuBuffer;
		}
		/// <summary>
		/// �����I�ȊJ��
		/// </summary>
		void Release();
	private:
		ID3D11Buffer*	m_gpuBuffer = nullptr;	//GPUBuffer
	};
}