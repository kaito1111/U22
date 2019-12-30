/// <summary>
/// GPUバッファクラス
/// </summary>
/// <remarks>
/// 基底クラス
/// </remarks>

#pragma once

namespace myEngine {
	class GPUBuffer
	{
	public:
		GPUBuffer();
		virtual ~GPUBuffer();
		/// <summary>
		/// GPUBufferの作成
		/// </summary>
		/// <param name="pInitData">初期データ</param>
		/// <param name="bufferDesc">バッファ定義</param>
		/// <returns>成功、失敗</returns>
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/// <summary>
		/// ID3D11Bufferの取得
		/// </summary>
		/// <returns>ID3D11Buffer</returns>
		ID3D11Buffer*& GetBody()
		{
			return m_gpuBuffer;
		}
		/// <summary>
		/// 明示的な開放
		/// </summary>
		void Release();
	private:
		ID3D11Buffer*	m_gpuBuffer = nullptr;	//GPUBuffer
	};
}