#pragma once

/*!
 *@brief	グラフィックスエンジン。
 */


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
	/// <summary>
	/// レンダーコンテキストの取得
	/// </summary>
	/// <returns></returns>
	//myEngine::RenderContext& GetRenderContext()
	//{
	//	return m_renderContext;
	//}
	/// <summary>
	/// D3D即時デバイスコンテキストの取得
	/// </summary>
	/// <returns></returns>
	ID3D11DeviceContext* GetD3DImmediateDeviceContext() const
	{
		return m_pImmediateContext;
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
	ID3D11DeviceContext*	m_pImmediateContext = NULL;					//即時コンテキスト
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。	
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファビューポート
	IDXGISwapChain*			m_pSwapChain = NULL;						//スワップチェイン。
	ID3D11RenderTargetView* m_backBuffer = NULL;						//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;					//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;						//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;					//デプスステンシルビュー。
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;			//エフェクサーレンダー
	Effekseer::Manager* m_manager = nullptr;							//エフェクトマネジャー


};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン