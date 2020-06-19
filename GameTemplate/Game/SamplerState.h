/// <summary>
/// �T���v���[�X�e�[�g
/// </summary>

#pragma once

namespace myEngine {

	class SamplerState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		SamplerState()
		{
		}
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~SamplerState()
		{
			Release();
		}
		/// <summary>
		/// ���
		/// </summary>
		void Release()
		{
			//auto a = m_samplerState;
			if (m_samplerState != nullptr) {
				m_samplerState->Release();
				m_samplerState = nullptr;
			}
		}
		/// <summary>
		/// �T���v���[�X�e�[�g�쐬
		/// </summary>
		/// <param name="desc">�������f�[�^�[</param>
		/// <returns></returns>
		bool Create(const D3D11_SAMPLER_DESC& desc);
		/// <summary>
		/// �T���v���[�X�e�[�g���擾
		/// </summary>
		/// <returns></returns>
		ID3D11SamplerState*& GetBody()
		{
			return m_samplerState;
		}
	private:
		ID3D11SamplerState*		m_samplerState = nullptr;	//�T���v���[�X�e�[�g

	};

}

