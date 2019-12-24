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
		/// <summary>
		/// StructuredBuffer用のSRVを作成
		/// </summary>
		/// <param name="structuredBuffer">ストラクチャーバッファ</param>
		/// <returns>クリエイトできるか</returns>
		bool Create(StructuredBuffer& structuredBuffer);
		/// <summary>
		/// テクスチャ用のSRVを作成
		/// </summary>
		/// <param name="texture">テクスチャ</param>
		/// <returns>クリエイトできるか</returns>
		bool Create(ID3D11Texture2D* texture);
		/// <summary>
		/// DDSファイルからテクスチャのSRVを作成
		/// </summary>
		/// <param name="fileName">ファイル名</param>
		/// <returns>作成できたか</returns>
		bool CreateFromDDSTextureFromFile(const wchar_t* fileName);
		/// <summary>
		/// 明示的な開放
		/// </summary>
		/// <remarks>
		/// 明示的に開放する場合使用
		/// </remarks>
		void Release();
	private:
		ID3D11ShaderResourceView*	m_srv = nullptr;		//SRV
		bool						m_isValid = false;		//有効なデータ？
	};
}


