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
	/// 開放
	/// </summary>
	void ShaderResourceView::Release()
	{
		if (m_srv != nullptr) {
			m_srv->Release();
			m_srv = nullptr;
		}
		//無効なデータフラグ
		m_isValid = false;
	}
	/// <summary>
	/// 
	/// </summary>
	/*
	bool ShaderResourceView::Create(StructuredBuffer& structuredBuffer)
	{
		//データの解放(初期化)
		Release();
		ID3D11Buffer* pBuf = structuredBuffer.GetBody();

	}
	*/
}
