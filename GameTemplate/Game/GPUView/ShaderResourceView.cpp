#include "stdafx.h"
#include "ShaderResourceView.h"
#include "StructuredBuffer.h"

namespace myEngine {
	ShaderResourceView::ShaderResourceView()
	{
	}
	ShaderResourceView::~ShaderResourceView()
	{
	}
	/// <summary>
	/// 開放
	/// </summary>
	void ShaderResourceView::Release()
	{
		if (m_srv != nullptr) {
			m_srv->Release();
			m_srv = nullptr;
		}
		//無効なデータフラグ
		m_isValid = false;
	}

	bool ShaderResourceView::Create(StructuredBuffer& structuredBuffer)
	{
		//データの解放(初期化)
		Release();
		//ID3D11バッファーの取得
		ID3D11Buffer* pBuf = structuredBuffer.GetBody();
		if (pBuf != nullptr) {
			//バッファリソースの情報
			D3D11_BUFFER_DESC descBuf;
			/*
			引数で渡した値を0で埋めてくれる関数です
			詳細については参考メモに書いてあるので見てください
			*/
			//恐らく初期化処理です
			ZeroMemory(&descBuf, sizeof(descBuf));
			//pBufで初期化したバッファリソースの値を持ってくる？
			pBuf->GetDesc(&descBuf);

			//シェーダーリソースビュー
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			//初期化
			ZeroMemory(&desc, sizeof(desc));
			//リソースがバッファーですよっていうフラグをたてる
			desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			//最初にビューに適用するインデックス(頂点)の番号
			desc.BufferEx.FirstElement = 0;


			desc.Format = DXGI_FORMAT_UNKNOWN;
		}
		return false;
	}
}
