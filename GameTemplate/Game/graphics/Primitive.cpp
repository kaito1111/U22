#include "stdafx.h"
#include "Primitive.h"
#include "GPUBuffer/IndexBuffer.h"

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

	//void Primitive::Draw(RenderContext& rc)
	//{
	//	//頂点バッファ設定
	//	rc.IASetVertexBuffer(m_vertexBuffer);
	//	rc.IASetIndexBuffer(m_indexBuffer);
	//	//プリミティブトポロジー
	//	rc.IASetPrimitiveToporogy(m_toology);
	//	//描画
	//	rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	//}

	void Primitive::Draw(ID3D11DeviceContext& dc)
	{
		UINT ofset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		dc.IASetVertexBuffers(0, 1, &m_vertexBuffer.GetBody(), &stride, &ofset);
		auto type = m_indexBuffer.GetIndexType();
		dc.IASetIndexBuffer(
			m_indexBuffer.GetBody(),
			type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
			0
		);
		//プリミティブのトポロジーを設定。
		dc.IASetPrimitiveTopology(m_toology);
		//描画。
		dc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}

	void Primitive::Draw(ID3D11DeviceContext& rc, int numVertex)
	{
		//頂点バッファを設定。
		UINT ofset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		rc.IASetVertexBuffers(0, 1, &(m_vertexBuffer.GetBody()), &stride, &ofset);
		//プリミティブのトポロジーを設定。
		rc.IASetPrimitiveTopology(m_toology);
		//描画。
		rc.Draw(numVertex, 0);
	}
}

