/// <summary>
/// レンダリングコンテキスト
/// 描画処理のためのデータの集合体
/// </summary>

#pragma once

/*
いるもの
DrawIndexed
Draw
UpdateSubresource
VSSetConstantBuffer
PSSetConstantBuffer
PSSetShaderResource
PSSetShader
VSSetShader
*/
#include "graphics/Shader.h"
#include "GPUBuffer/VertexBuffer.h"
#include "GPUBuffer/IndexBuffer.h"
#include "GPUBuffer/StructuredBuffer.h"
#include "ConstantBuffer.h"
#include "GPUView/ShaderResourceView.h"
#include "GPUView/UnorderedAccessView.h"

namespace myEngine {
	class VertexBuffer;

	class RenderContext
	{
	public:
		RenderContext();
		~RenderContext();
		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="pD3DDeviceContext">D3Dデバイスコンテキスト</param>
		/// <param name="pD3DDeferredDeviceContext">D3Dデバイスコンテキスト</param>
		void Init(ID3D11DeviceContext* pD3DDeviceContext, ID3D11DeviceContext* pD3DDeferredDeviceContext);
		/// <summary>
		/// 頂点バッファの設定
		/// </summary>
		/// <param name="vertexBuffer">頂点バッファ</param>
		void IASetVertexBuffer(VertexBuffer& vertexBuffer)
		{
			//UINT = 値の取れる範囲が倍のint型
			UINT offset = 0;
			//頂点バッファのストライドの取得
			UINT stride = vertexBuffer.GetStride();
		}
		/// <summary>
		/// インデックスバッファ
		/// </summary>
		/// <param name="indexBuffer">インデックスバッファ</param>
		void IASetIndexBuffer(IndexBuffer& indexBuffer)
		{
			//インデックスの型
			IndexBuffer::EnIndexType type = indexBuffer.GetIndexType();
			m_pD3DDeviceContext->IASetIndexBuffer(
				indexBuffer.GetBody(),
				//条件演算子 exp1 ? exp2:exp3	expが真ならexp2を、偽ならexp3を
				//16型じゃないなら32型をフォーマット(初期化
				type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
				0
			);
		}
		/// <summary>
		/// プリミティブのトポロジーを設定
		/// </summary>
		/// <param name="topology">トポロジー</param>
		void IASetPrimitiveToporogy(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			m_pD3DDeviceContext->IASetPrimitiveTopology(topology);
		}
		/// <summary>
		/// VSステージに定数バッファを設定
		/// </summary>
		/// <param name="slotNo">スロット番号</param>
		/// <param name="cb">定数バッファ</param>
		void VSSetConstantBuffer(
			UINT slotNo,
			ConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/// <summary>
		/// VSステージにSRVを設定
		/// </summary>
		/// <param name="slotNo">スロット番号</param>
		/// <param name="srv">SRV</param>
		void VSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			m_pD3DDeviceContext->VSGetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/// <summary>
		/// VSステージからSRVを外す
		/// </summary>
		/// <param name="slotNo">スロット番号</param>
		void VSUnsetShaderResource(int slotNo)
		{
			ID3D11ShaderResourceView* view[] = {
				NULL
			};
			m_pD3DDeviceContext->VSSetShaderResources(slotNo, 1, view);
		}
		/// <summary>
		/// PSステージに定数バッファを設定
		/// </summary>
		/// <param name="slotNo">スロット番号</param>
		/// <param name="cb">定数バッファ</param>
		void PSSetConstantBuffer(
			UINT slotNo,
			ConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
	private:
		ID3D11DeviceContext*			m_pD3DDeviceContext = nullptr;
	};
}


