#include "stdafx.h"
#include "ShaderResourceView.h"
#include "GPUBuffer/StructuredBuffer.h"
#include "myEngine.h"

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
	/// <summary>
	/// StructuredBuffer用のSRVを作成
	/// </summary>
	/// <param name="structuredBuffer">ストラクチャーバッファー</param>
	/// <returns>データが有効かのフラグ</returns>
	/// <remarks>
	/// trueフラグがたったらSRVが使えるように
	/// </remarks>
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

			//シェーダーリソースビューの情報
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			//初期化
			ZeroMemory(&desc, sizeof(desc));
			//リソースがバッファーですよっていうフラグをたてる
			desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			//最初にビューに適用するインデックス(頂点)の番号
			desc.BufferEx.FirstElement = 0;

			//状態の初期化処理
			desc.Format = DXGI_FORMAT_UNKNOWN;
			//左辺::バッファリソースの要素数
			//右辺::バッファリソースのサイズ/ストラクチャーバッファーのサイズ？
			desc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

			//hrでエラーがないかの判定しつつ、SRVの作成
			HRESULT hr = graphicsEngine().GetD3DDevice()->CreateShaderResourceView(pBuf, &desc, &m_srv);
			if (FAILED(hr)) {
				//エラー
				return false;
			}
		}
		//有効なデータ！
		m_isValid = true;
		return true;
	}
	bool ShaderResourceView::CreateFromDDSTextureFromFile(const wchar_t* fileName)
	{
		//初期化
		Release();
		//これも恐らく全部初期化
		//DirectX...もHRESULT型だから通る
		HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
			graphicsEngine().GetD3DDevice(),	//D3DDevice
			fileName,							//ファイル名
			0,									//サイズ
			D3D11_USAGE_DEFAULT,				//CPUがGPUがアクセス可能かどうかのフラグ
			D3D11_BIND_SHADER_RESOURCE,			//バインドフラグ ex結び付け方のフラグ
			0,									//？CPUアクセス回数？
			0,									//？その他のアクセス回数？ miscがその他
			false,								//？SRGBっていうカラースペース使うかどうか的な奴？
			nullptr,							//テクスチャのポインタ
			&m_srv								//srv
		);
		if (FAILED(hr)) {
			//エラーメッセージがでる予定
			return false;
		}
		return true;
	}
}
