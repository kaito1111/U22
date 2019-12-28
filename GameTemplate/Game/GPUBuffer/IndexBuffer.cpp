#include "stdafx.h"
#include "IndexBuffer.h"
#include "myEngine.h"

namespace myEngine {
	IndexBuffer::IndexBuffer()
	{
	}
	IndexBuffer::~IndexBuffer()
	{
		//開放
		Release();
	}
	void IndexBuffer::Release()
	{
		if (m_indexBuffer) {
			m_indexBuffer->Release();
			m_indexBuffer = nullptr;
		}
		m_isCreated = false;
	}
	bool IndexBuffer::Create(int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer)
	{
		//初期化
		Release();

		int stride = 0;
		if (indexType == enIndexType_16) {
			//16bitなら
			stride = 2;
		}
		else {
			//32bitなら
			stride = 4;
		}
		//インデックスタイプ
		m_indexType = indexType;
		//インデックスの数
		m_numIndex = numIndex;
		//バッファリソース
		D3D11_BUFFER_DESC bd;
		//bdのポインタを初期化
		ZeroMemory(&bd, sizeof(bd));
		//GPUアクセスフラグをデフォルトに
		bd.Usage = D3D11_USAGE_DEFAULT;
		//ストラクチャバッファのサイズ
		bd.StructureByteStride = stride;
		//インデックスバッファのサイズ
		bd.ByteWidth = stride * numIndex;
		//インデックスバッファフラグ
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//よくわからんフラグ
		bd.CPUAccessFlags = 0;
		
		//サブリソース(テクスチャとか？)
		D3D11_SUBRESOURCE_DATA InitData;
		//サブリソースの初期化
		ZeroMemory(&InitData, sizeof(InitData));
		//ソースインデックスバッファの代入 pSysMemが初期化ポインタ
		InitData.pSysMem = pSrcIndexBuffer;

		//エラー検出しつつCreate
		HRESULT hr = graphicsEngine().GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
		if (FAILED(hr)) {
			//失敗
			return false;
		}
		//成功
		m_isCreated = true;
		return true;
	}
}

