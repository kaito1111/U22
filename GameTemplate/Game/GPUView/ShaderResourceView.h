/// <summary>
/// ShaderResourceView
/// </summary>

#pragma once

namespace myEngine {
	class StructuredBuffer;
	/// <summary>
	/// ShaderResourceView
	/// </summary>
	/// <remarks>
	/// テクスチャやストラクチャーバッファなどの
	/// シェーダーで使用するリソースで使用するビュー
	/// </remarks>
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();
		bool Create(StructuredBuffer& structuredBuffer);
	};
}


