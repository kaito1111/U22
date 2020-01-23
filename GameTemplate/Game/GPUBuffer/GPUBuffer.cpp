#include "stdafx.h"
#include "GPUBuffer.h"
#include "myEngine.h"

namespace myEngine {
	GPUBuffer::GPUBuffer()
	{
	}
	GPUBuffer::~GPUBuffer()
	{
		Release();
	}
	//開放
	void GPUBuffer::Release()
	{
		if (m_gpuBuffer != nullptr) {
			m_gpuBuffer->Release();
			m_gpuBuffer = nullptr;
		}
	}
	//作成
	bool GPUBuffer::Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc)
	{
		Release();
		HRESULT hr;
		if (pInitData) {
			//サブリソース
			D3D11_SUBRESOURCE_DATA InitData;
			//初期化ポインタ
			InitData.pSysMem = pInitData;
			hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, &InitData, &m_gpuBuffer);
		}
		else {
			hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_gpuBuffer);
		}
		if (FAILED(hr)) {
			//エラー
			return false;
		}
		//成功
		return true;
	}
}

