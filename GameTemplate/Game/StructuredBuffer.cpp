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
		//モデルがnullポインタじゃないなら
		if (pInitData) {
			//サブリソース
			D3D11_SUBRESOURCE_DATA InitData;
			//モデルの代入（初期化
			InitData.pSysMem = pInitData;
			//エラーがでないかの判定(こっちはS_OKを返す)
			hr = m_pd3dDevice->CreateBuffer(&bufferDesc, &InitData, &m_sturcturedBuffer);
		}
		//モデルがNULLなら
		else {
			//エラーがでないかの判定(こっちはFAILEDを返す)
			hr = m_pd3dDevice->CreateBuffer(&bufferDesc, NULL, &m_sturcturedBuffer);
		}
		//hrの値が失敗なら
		if (FAILED(hr)) {
			//処理終了
			return false;
		}

		return true;
	}
}

