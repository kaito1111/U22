#include "stdafx.h"
#include "StructuredBuffer.h"
/// <summary>
/// StructuredBuffer
/// </summary>
/// <remarks>
/// StructuredBuffer::全ての要素が同じサイズを持つバッファ
/// Buffer::一時的に保存しておくためのもの
/// </remarks>

namespace myEngine {
	StructuredBuffer::StructuredBuffer()
	{
	}
	StructuredBuffer::~StructuredBuffer()
	{
	}
	//バッファの解放
	void StructuredBuffer::Release()
	{
		if (m_sturcturedBuffer != nullptr) {
			m_sturcturedBuffer->Release();
			m_sturcturedBuffer = nullptr;
		}
	}
	//バッファの作成
	bool StructuredBuffer::Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc)
	{
		//初期化処理
		Release();
		//機能としてはbool型 参考メモにURL貼っときます。
		HRESULT hr;
		//nullポインタじゃないなら
		if (pInitData) {
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = pInitData;
		}
	}
}

