#pragma once

/// <summary>
/// レンダリングモード
/// </summary>
enum EnRenderMode {
	enRenderMode_Normal,			//通常描画
	enRenderMode_CreateSilhouette,	//シルエット描画
	enRenderMode_CreateShadowMap,	//シャドウマップ生成
	enRenderMode_Num				//レンダリングモードの数
};	

/*!
 *@brief	グラフィックスエンジン。
 */

#include "LightManager.h"
#include "ShadowMap.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/// <summary>
	/// エフェクサーの初期化
	/// </summary>
	void InitEffekseer();
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice() const
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// エフェクサーマネージャの取得
	/// </summary>
	/// <returns></returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_manager;
	}
	/// <summary>
	/// エフェクサーレンダーの取得
	/// </summary>
	/// <returns></returns>
	EffekseerRenderer::Renderer* GetEffekseerRenderer()
	{
		return m_effekseerRenderer;
	}
	/// <summary>
	/// ライトマネージャーの取得
	/// </summary>
	/// <returns></returns>
	myEngine::LightManager* GetLigManager()
	{
		return m_ligManager;
	}

	myEngine::ShadowMap* GetShadowMap()
	{
		return m_shadowMap;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;								//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;						//D3D11デバイス。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;					//D3D11デバイスコンテキスト。		
	IDXGISwapChain*			m_pSwapChain = NULL;						//スワップチェイン。
	ID3D11RenderTargetView* m_backBuffer = NULL;						//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;					//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;						//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;					//デプスステンシルビュー。
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;			//エフェクサーレンダー
	Effekseer::Manager* m_manager = nullptr;							//エフェクトマネジャー
	myEngine::LightManager* m_ligManager;								//ライトマネージャー グラフィックエンジンでNewGOしてる
	myEngine::ShadowMap* m_shadowMap;												//シャドウマップ

	//汚かったグラフィックエンジンから取り除いた変数一覧
	/*
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファビューポート
	ID3D11DeviceContext*	m_pImmediateContext = NULL;					//即時コンテキスト
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	D3D11_FEATURE_DATA_THREADING m_featureDataThreading;
	*/
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン