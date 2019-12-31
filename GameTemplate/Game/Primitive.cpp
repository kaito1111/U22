#include "stdafx.h"
#include "Primitive.h"

namespace myEngine {
	Primitive::Primitive()
	{
	}
	Primitive::~Primitive()
	{
		Release();
	}
	//開放
	void Primitive::Release()
	{
		m_vertexBuffer.Release();
		m_indexBuffer.Release();
	}
	//プリミティブの作成
	bool Primitive::Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		IndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer
	)
	{
		//初期化
		Release();
		//接続形態
		m_toology = topology;
		//頂点バッファの作成とエラー検出
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
		if (!result) {
			//エラー
			return false;
		}
		if (pSrcIndexBuffer) {
			//インデックス作成とエラー検出
			result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
			if (!result) {
				//エラー
				return false;
			}
		}
		//成功
		return true;
	}

	void Primitive::Draw(RenderContext& rc)
	{
		//頂点バッファ設定
		rc.IASetVertexBuffer(m_vertexBuffer);
		rc.IASetIndexBuffer(m_indexBuffer);
		//プリミティブトポロジー
		rc.IASetPrimitiveToporogy(m_toology);
		//描画
		rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}

	void Primitive::Draw(RenderContext& rc, int numVertex)
	{
		rc.IASetVertexBuffer(m_vertexBuffer);
		//トポロジー
		rc.IASetPrimitiveToporogy(m_toology);
		//描画
		rc.Draw(numVertex, 0);
	}
}

