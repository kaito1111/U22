#include "stdafx.h"
#include "ShaderResourceView.h"
#include "StructuredBuffer.h"

namespace myEngine {
	ShaderResourceView::ShaderResourceView()
	{
	}
	ShaderResourceView::~ShaderResourceView()
	{
	}
	/// <summary>
	/// �J��
	/// </summary>
	void ShaderResourceView::Release()
	{
		if (m_srv != nullptr) {
			m_srv->Release();
			m_srv = nullptr;
		}
		//�����ȃf�[�^�t���O
		m_isValid = false;
	}
	/// <summary>
	/// 
	/// </summary>
	/*
	bool ShaderResourceView::Create(StructuredBuffer& structuredBuffer)
	{
		//�f�[�^�̉��(������)
		Release();
		ID3D11Buffer* pBuf = structuredBuffer.GetBody();

	}
	*/
}
