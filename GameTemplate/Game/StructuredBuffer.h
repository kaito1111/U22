#pragma once
#include "GPUView/ShaderResourceView.h"
#include "GPUView/UnorderedAccessView.h"
namespace myEngine {
	class StructuredBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();
		/// <summary>
		/// StructuredBufferを作成
		/// </summary>
		/// <remarks>
		/// ---引数について---
		/// pInitData::テクスチャです。どんな型でも入れれるようにvoid型
		/// bufferDesc::バッファーの情報とかがいろいろ入ってるやつです
		/// D3D11系統のクラスの解説URL、参考メモに貼っときます
		/// </remarks>
		/// <param name="pInitData">初期データ</param>
		/// <param name="bufferDesc">バッファ定義</param>
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/// <summary>
		/// ID3D11Buffer*の取得
		/// </summary>
		/// <returns>ストラクチャーバッファ</returns>
		/// <remarks>
		/// *&::間接参照演算子→ポインタをとったやつの本体を参照
		/// ポインタを返すんじゃなくて本体を返す
		/// 参考メモにURL貼っときます
		/// </remarks>
		ID3D11Buffer*& GetBody()
		{
			return m_sturcturedBuffer;
		}
		/// <summary>
		///	データの開放処理
		/// </summary>
		/// <remarks>
		/// 基本デストラクタで呼び出しだけど、
		/// 明示的なタイミングで使いたいときに使ってね
		/// </remarks>
		void Release();
		/// <summary>
		/// SRVの取得
		/// </summary>
		/// <returns>SRV</returns>
		ShaderResourceView& GetSRV()
		{
			return m_srv;
		}
		/// <summary>
		/// UAVの取得
		/// </summary>
		/// <returns>UAV</returns>
		UnorderedAccessView& GetUAV()
		{
			return m_uav;
		}
	private:
		ID3D11Device*			m_pd3dDevice;					//3D11Device
		ID3D11Buffer*			m_sturcturedBuffer = nullptr;	//StructuredBuffer
		ShaderResourceView		m_srv;							//SRV
		UnorderedAccessView		m_uav;							//UAV
	};
}


