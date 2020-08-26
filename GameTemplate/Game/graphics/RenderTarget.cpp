#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Release()
{
	//レンダーターゲットの解放
	if (m_renderTargetTex != nullptr)
	{
		m_renderTargetTex->Release();
	}
	//レンダーターゲットビューの解放
	if (m_renderTargetView != nullptr)
	{
		m_renderTargetView->Release();
	}
	//レンダーターゲットSRVの解放
	if (m_renderTargetSRV != nullptr)
	{
		m_renderTargetSRV->Release();
	}
	//デプスステンシルテクスチャをの解放
	if (m_depthStencilTex != nullptr)
	{
		m_depthStencilTex->Release();
	}
	//デプスステンシルビュー
	if (m_depthStencilView != nullptr)
	{
		m_depthStencilView->Release();
	}
}

void RenderTarget::Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat)
{
	//デバイス取得
	auto dv = Engine().GetGraphicsEngine().GetD3DDevice();

	//レンダリングターゲットとなるテクスチャ作成
	D3D11_TEXTURE2D_DESC texDesc = { 0 };
	{
		//テクスチャの作成

		//テクスチャの横の解像度
		texDesc.Width = w;
		m_width = w;
		//テクスチャの縦の解像度
		texDesc.Height = h;
		m_height = h;
		//ミニマップレベル
		texDesc.MipLevels = 1;
		//テクスチャの配列サイズ
		texDesc.ArraySize = 1;
		//テクスチャのフォーマット
		//RGBAの各要素8Bitの32Bitフォーマット
		texDesc.Format = texFormat;
		//テクスチャの使用用途を決める
		//レンダリングターゲットのテクスチャは
		//レンダリングターゲット、ShaderResourceView, UnorderedAccessViewとしてバインド
		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		//マルチサンプリングの数
		texDesc.SampleDesc.Count = 1;
		//マルチサンプリングの品質
		texDesc.SampleDesc.Quality = 0;
		//テクスチャの読み書きのされ方
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		//CPUからのアクセスの仕方
		texDesc.CPUAccessFlags = 0;
		//0
		texDesc.MiscFlags = 0;
		//テクスチャ作成
		dv->CreateTexture2D(&texDesc, nullptr, &m_renderTargetTex);

		//nullチェック
		if (m_renderTargetTex == nullptr) {
			/*---throw---
			descの初期化の値を確認せよ
			  ---throw---*/
			throw;
		}
	}

	//レンダリングターゲットビューの作成
	{
		//レンダリングターゲットビューの作成

		//レンダリングターゲットビューを作成するためのデータ設定
		D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
		//フォーマットはテクスチャと同じ
		viewDesc.Format = texDesc.Format;
		//2Dテクスチャを扱うことを指定
		viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		//0
		viewDesc.Texture2D.MipSlice = 0;
		//レンダリングターゲットビューの作成
		dv->CreateRenderTargetView(m_renderTargetTex, &viewDesc, &m_renderTargetView);
	}
	//シェーダーリソースビュー
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		//フォーマットはテクスチャと同じでよい。
		srvDesc.Format = texDesc.Format;
		//2次元テクスチャとして扱う。
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		//ミップマップレベルもテクスチャと同じでよい。
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
		//0でいい。
		srvDesc.Texture2D.MostDetailedMip = 0;
		//SRVを作成する。
		dv->CreateShaderResourceView(m_renderTargetTex, &srvDesc, &m_renderTargetSRV);

	}
	//デプスステンシルテクスチャの作成
	D3D11_TEXTURE2D_DESC depthTexDesc = texDesc;
	{
		//デプスステンシルビューにバインドする。
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//32bit浮動小数点のデプスステンシルバッファを作成する。
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//デプスステンシルテクスチャを作成する。
		dv->CreateTexture2D(&depthTexDesc, nullptr, &m_depthStencilTex);
	}
	//デプスステンシルビューの作成
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		//フォーマットは深度ステンシルと同じにする。
		depthStencilViewDesc.Format = depthTexDesc.Format;
		//2Dテクスチャを扱うことを指定する。
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//0でいい。
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		//0でいい。
		depthStencilViewDesc.Flags = 0;
		//デプスステンシルビューを作成。
		dv->CreateDepthStencilView(m_depthStencilTex, &depthStencilViewDesc, &m_depthStencilView);
	}
	//ビューポート
	{
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = w;
		m_viewport.Height = h;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;
	}
}

void RenderTarget::ClearRenderTarget(float* clearColor)
{
	//デバイス取得
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	//クリア
	dc->ClearRenderTargetView(m_renderTargetView, clearColor);
	dc->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
