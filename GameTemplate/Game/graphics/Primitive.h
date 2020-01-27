/// <summary>
/// プリミティブ
/// </summary>

#pragma once

#include "GPUBuffer/IndexBuffer.h"
#include "GPUBuffer/vertexBuffer.h"

namespace myEngine {
	class Primitive
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Primitive();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~Primitive();
		/// <summary>
		/// プリミティブ作成
		/// </summary>
		/// <param name="topologe">トポロジー(接続形態)</param>
		/// <param name="numVertex">頂点の数</param>
		/// <param name="vertexStride">頂点ストライド</param>
		/// <param name="pSrcVertexBuffer">ソースとなる頂点バッファ</param>
		/// <param name="numIndex">インデックスの数</param>
		/// <param name="indexType">インデックスの型</param>
		/// <param name="pSrcIndexBuffer">ソースとなるインデックスバッファ</param>
		/// <returns>true:成功　false:失敗</returns>
		/// <remarks>
		/// D3D_PRIMITIVE_TOPOLOGY
		///	バインド(結びつけされた)頂点データをどのように解釈するかの値がある列挙
		/// 詳しくは参考Memoで
		/// vertexStride
		/// ストライド → 配列内要素の間隔 
		/// 詳しくは参考Memoで
		/// </remarks>
		bool Create(
			D3D_PRIMITIVE_TOPOLOGY  topologe,
			int numVertex,
			int vertexStride,
			void* pSrcVertexBuffer,
			int numIndex,
			IndexBuffer::EnIndexType indexType,
			void* pSrcIndexBuffer
		);
		/// <summary>
		/// 明示的に開放
		/// </summary>
		void Release();
		/// <summary>
		/// バーテックスバッファの描画
		/// </summary>
		void Draw(ID3D11DeviceContext& dc, int numVertex);
		/// <summary>
		/// インデックスバッファの描画
		/// </summary>
		/// <param name="dc"></param>
		/// <param name="numVertex"></param>
		void Draw(ID3D11DeviceContext& dc);
		/// <summary>
		/// 頂点バッファの取得
		/// </summary>
		/// <returns>頂点バッファ</returns>
		VertexBuffer& GetVertexBuffer()
		{
			return m_vertexBuffer;
		}
	private:
		VertexBuffer			m_vertexBuffer;		//頂点バッファ
		IndexBuffer				m_indexBuffer;		//インデックスバッファ
		D3D_PRIMITIVE_TOPOLOGY	m_toology;			//トポロジー
	};
}


