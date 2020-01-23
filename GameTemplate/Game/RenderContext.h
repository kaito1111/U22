/// <summary>
/// レンダリングコンテキスト
/// 描画処理のためのデータの集合体
/// </summary>

#pragma once

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
				//条件演算子 (exp1 ? exp2:exp3)	expが真ならexp2を、偽ならexp3を
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
		void PSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			m_pD3DDeviceContext->PSSetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/// <summary>
		/// ピクセルシェーダー
		/// </summary>
		/// <param name="shader">頂点シェーダー</param>
		void PSSetShader(Shader& shader)
		{
			m_pD3DDeviceContext->PSSetShader((ID3D11PixelShader*)shader.GetBody(), NULL, 0);
		}
		/// <summary>
		/// 頂点シェーダー設定
		/// </summary>
		/// <param name="shader">頂点シェーダー</param>
		void VSSetShader(Shader& shader)
		{
			m_pD3DDeviceContext->VSSetShader((ID3D11VertexShader*)shader.GetBody(), NULL, 0);
		}
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="vertexCount">頂点の数</param>
		/// <param name="startVertexCount">描画を開始する頂点の位置 基本0</param>
		void Draw(
			unsigned int vertexCount,
			unsigned int startVertexCount
		)
		{
			m_pD3DDeviceContext->Draw(vertexCount, startVertexCount);
		}
		/// <summary>
		/// インデックス付き描画
		/// </summary>
		/// <param name="IndexCount">インデックスの数</param>
		/// <param name="StartIndexLocation">描画を開始するインデックスの位置 基本0</param>
		/// <param name="BaseVertexLocation">ベース頂点インデックス。基本0</param>
		void DrawIndexed(
			//_In_って？　参考Memo参照
			_In_ UINT IndexCount,
			_In_ UINT StartIndexLocation,
			_In_ UINT BaseVertexLocation
		)
		{
			m_pD3DDeviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
		}
		template<class TBuffer, class SrcBuffer>
		/// <summary>
		/// サブリソース更新
		/// </summary>
		/// <param name="gpuBuffer">コピー先</param>
		/// <param name="buffer">コピー元</param>
		/// <remarks>
		/// コメントが間違ってるかも　確認でき次第、書き換えます
		/// ★バグ出る可能性あり
		/// </remarks>
		void UpdateSubResourse(TBuffer& gpuBuffer, const SrcBuffer* buffer)
		{
			if (gpuBuffer.GetBody() != nullptr) {
				m_pD3DDeviceContext->UpdateSubresource(gpuBuffer.GetBody(), 0, NULL, buffer, 0, 0);
			}
		}
	private:
		ID3D11DeviceContext*			m_pD3DDeviceContext = nullptr;
	};
}


