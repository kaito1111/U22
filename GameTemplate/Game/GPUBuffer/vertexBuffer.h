/// <summary>
/// 頂点バッファ
/// </summary>

#pragma once

namespace myEngine {
	class VertexBuffer
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		VertexBuffer();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~VertexBuffer();
		/// <summary>
		/// 頂点バッファの作成
		/// </summary>
		/// <param name="numVertex">頂点数</param>
		/// <param name="stride">頂点ストライド</param>
		/// <param name="pSrcVertexBuffer">ソース頂点バッファ</param>
		/// <returns>成功、失敗</returns>
		bool Create(int numVertex, int stride, const void* pSrcVertexBuffer);
		/// <summary>
		/// 開放
		/// </summary>
		void Release();
		/// <summary>
		/// 頂点ストライドを取得
		/// </summary>
		int GetStride() const
		{
			return m_stride;
		}
		/// <summary>
		/// ID3D11Bufferを取得
		/// </summary>
		ID3D11Buffer*& GetBody()
		{
			return m_vertexBuffer;
		}
	private:
		ID3D11Buffer*	m_vertexBuffer = nullptr;	//頂点バッファ
		int				m_stride = 0;				//頂点ストライド
	};

}

