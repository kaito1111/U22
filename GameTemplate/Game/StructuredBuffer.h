#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer();
	~StructuredBuffer();
	/// <summary>
	/// StructuredBuffer���쐬
	/// </summary>
	/// <param name="pInitData">�����f�[�^</param>
	/// <param name="bufferDesc">�o�b�t�@��`</param>
	bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
	/// <summary>
	/// aaaa
	/// </summary>
};

