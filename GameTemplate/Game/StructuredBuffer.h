#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer();
	~StructuredBuffer();
	/// <summary>
	/// StructuredBufferを作成
	/// </summary>
	/// <param name="pInitData">初期データ</param>
	/// <param name="bufferDesc">バッファ定義</param>
	bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
	/// <summary>
	/// aaaa
	/// </summary>
};

