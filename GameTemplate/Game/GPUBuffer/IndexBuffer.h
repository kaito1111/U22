/// <summary>
/// インデックスバッファ
/// </summary>
/// <remarks>
/// ？？インデックスバッファ？？
///	かぶってる頂点とかいらないので無駄をなくそうっていうバッファ
/// </remarks>

#pragma once

namespace myEngine {
	class IndexBuffer
	{
	public:
		/// <summary>
		/// インデックスの型
		/// </summary>
		/// <remarks>
		/// 列挙型
		/// </remarks>
		enum EnIndexType {
			enIndexType_16,		//16ビットのインデックス
			enIndexType_32,		//32ビットのインデックス
		};
		/// <summary>
		/// コンストラクタ
		/// </summary>
		IndexBuffer();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~IndexBuffer();
		/// <summary>
		/// インデックスバッファ作成
		/// </summary>
		/// <param name="numIndex">インデックスの数</param>
		/// <param name="indexType">インデックスの型</param>
		/// <param name="pSrcIndexBuffer">ソースインデックスバッファ</param>
		/// <returns></returns>
		bool Create(int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer);
		/// <summary>
		/// 開放処理
		/// <para>明示的なタイミングで開放する場合呼ぶ</para>
		/// </summary>
		void Release();
		/// <summary>
		/// インデックスの型を取得
		/// </summary>
		/// <returns>インデックスの型</returns>
		EnIndexType GetIndexType() const
		{
			return m_indexType;
		}
		/// <summary>
		/// インデックスバッファの取得
		/// </summary>
		/// <returns>インデックス</returns>
		ID3D11Buffer* GetBody() const
		{
			return m_indexBuffer;
		}
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		unsigned int GetNumIndex() const
		{
			return m_numIndex;
		}
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool IsCreated() const
		{
			return m_isCreated;
		}
	private:
		bool			m_isCreated = false;			//インデックスバッファ作成されてる？
		ID3D11Buffer*	m_indexBuffer = nullptr;		//インデックスバッファ
		EnIndexType		m_indexType = enIndexType_16;	//インデックスバッファの型
		unsigned int	m_numIndex = 0;					//インデックスバッファの数
	};
}


