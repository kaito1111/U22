#include "stdafx.h"
#include "ConstantBuffer.h"

namespace myEngine {
	ConstantBuffer::ConstantBuffer()
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::Create(const void* pInitData, int bufferSize)
	{
		//定数バッファ用のバッファ定義
		D3D11_BUFFER_DESC bufferDesc;
		//バッファ定義の初期化
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		//アクセスフラグをデフォルト
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//16バイトアライメントに切り上げ→参考URL
		bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;
		//定数バッファとして結び付け
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		return GPUBuffer::Create(pInitData, bufferDesc);
	}
}

