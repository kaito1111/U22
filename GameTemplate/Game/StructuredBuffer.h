#pragma once
#include "GPUView/ShaderResourceView.h"
#include "GPUView/UnorderedAccessView.h"
namespace myEngine {
	class StructuredBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();
		/// <summary>
		/// StructuredBuffer���쐬
		/// </summary>
		/// <remarks>
		/// ---�����ɂ���---
		/// pInitData::�e�N�X�`���ł��B�ǂ�Ȍ^�ł�������悤��void�^
		/// bufferDesc::
		/// </remarks>
		/// <param name="pInitData">�����f�[�^</param>
		/// <param name="bufferDesc">�o�b�t�@��`</param>
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/// <summary>
		///	�f�[�^�̊J������
		/// </summary>
		/// <remarks>
		/// ��{�f�X�g���N�^�ŌĂяo�������ǁA
		/// �����I�ȃ^�C�~���O�Ŏg�������Ƃ��Ɏg���Ă�
		/// </remarks>
		void Release();
		/// <summary>
		/// SRV�̎擾
		/// </summary>
		/// <returns>SRV</returns>
		ShaderResourceView& GetSRV()
		{
			return m_srv;
		}
		/// <summary>
		/// UAV�̎擾
		/// </summary>
		/// <returns>UAV</returns>
		UnorderedAccessView& GetUAV()
		{
			return m_uav;
		}
	private:
		ID3D11Device*			m_pd3dDevice;					//3D11Device
		ID3D11Buffer*			m_sturcturedBuffer = nullptr;	//StructuredBuffer
		ShaderResourceView		m_srv;							//SRV
		UnorderedAccessView		m_uav;							//UAV
	};
}


