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

#include "light/LightManager.h"
#include "Shadow/ShadowMap.h"
#include "2D/Sprite.h"

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
	/// <summary>
	/// レンダリングターゲットの切り替え '深度ステンシルビューは変更しないVer'
	/// <para>ビューポートを指定しない場合はnullptrを送ってください</para>
	/// </summary>
	/// <param name="dc">デバコン</param>
	/// <param name="rtv">レンダリングターゲットビュー</param>
	/// <param name="dsv">深度ステンシルビュー</param>
	/// <param name="vp">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* dc, RenderTarget* rtv, D3D11_VIEWPORT* vp);
	/// <summary>
	/// レンダーターゲットを変更 '深度ステンシルビューも変更するVer' 
	/// <para>ビューポートを指定しない場合はnullptrを送ってください</para>
	/// </summary>
	/// <param name="dc">デバコン</param>
	/// <param name="rtv">レンダーターゲットビュー</param>
	/// <param name="dsv">デプスステンシルビュー</param>
	/// <param name="vp">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* dc, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv, D3D11_VIEWPORT* vp);
	/// <summary>
	/// レンダーターゲットとかのバックアップ
	/// </summary>
	void oldTarget();
	/// /// <summary>
	/// フォワードレンダーターゲット
	/// </summary>
	void OffScreenRenderTarget();
	/// <summary>
	/// ポストレンダーターゲット
	/// </summary>
	void PostRenderTarget();
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
	/// バックバッファーを取得
	/// </summary>
	/// <returns></returns>
	ID3D11RenderTargetView* GetBuckBuffer()
	{
		return m_backBuffer;
	}
	/// <summary>
	/// ライトマネージャーの取得
	/// </summary>
	/// <returns></returns>
	myEngine::LightManager* GetLigManager()
	{
		return m_ligManager;
	}
	/// <summary>
	/// シャドウマップを取得
	/// </summary>
	/// <returns></returns>
	myEngine::ShadowMap* GetShadowMap()
	{
		return m_shadowMap;
	}
	/// <summary>
	/// オフスクリーンレンダーターゲットを取得
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetOffScreenRenderTarget()
	{
		return m_mainRenderTarget;
	}
	/// <summary>
	/// スプライトバッチ取得。
	/// </summary>
	/// <returns></returns>
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		//m_spriteBatchのポインタ。
		return m_spriteBatch.get();
	}
	/// <summary>
	/// スプライトフォント取得。
	/// </summary>
	/// <returns></returns>
	DirectX::SpriteFont* GetSpriteFont() const
	{
		//m_spriteFontのポインタ。
		return m_spriteFont.get();
	}

	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();

	void PushRenderState()
	{
		m_renderStateStack.push(m_currentRenderState);
	}

	void SetRenderState()
	{
		m_currentRenderState = m_renderStateStack.top();
		m_renderStateStack.pop();
		m_pd3dDeviceContext->OMSetBlendState(m_currentRenderState.blendState, 0, 0xFFFFFFFF);
		m_pd3dDeviceContext->RSSetState(m_currentRenderState.rasterrizerState);
		m_pd3dDeviceContext->OMSetDepthStencilState(m_currentRenderState.depthStencilState, 0);
	}

private:
	struct SRenderState{
		ID3D11DepthStencilState*	depthStencilState = nullptr;	//!<現在のデプスステンシルステート。
		ID3D11RasterizerState*		rasterrizerState = nullptr;		//!<現在のラスタライザステート。
		ID3D11BlendState*			blendState = nullptr;			//!<現在のブレンドステート。
	};
private:
	D3D_FEATURE_LEVEL		m_featureLevel;								//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;						//D3D11デバイス。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;					//D3D11デバイスコンテキスト。		
	IDXGISwapChain*			m_pSwapChain = NULL;						//スワップチェイン。
	ID3D11RenderTargetView* m_backBuffer = NULL;						//バックバッファ。
	RenderTarget* m_mainRenderTarget = NULL;							//メインレンダーターゲット
	ID3D11RenderTargetView* m_frameBufferRenderTargetView;				//フレームRTV
	ID3D11DepthStencilView* m_frameBufferDepthStencilView;				//フレームDSV
	//ID3D11BlendState*		m_blendState = nullptr;								//ブレンドステート（テスト）
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームビューポート
	//ID3D11RasterizerState*	m_rasterizerState = NULL;					//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;						//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;					//デプスステンシルビュー。
	std::stack<SRenderState> m_renderStateStack;						//レンダーステートのスタック
	SRenderState			m_currentRenderState;						//レンダーステート
	myEngine::Sprite* m_copyMainRtToFrameBufferSprite;					//オフスクリーンレンダリング用のスプライト
	myEngine::LightManager* m_ligManager = nullptr;						//ライトマネージャー グラフィックエンジンでNewGOしてる
	myEngine::ShadowMap* m_shadowMap;									//シャドウマップ
	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;				//スプライトバッチ。
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;				//スプライトフォント。
	//汚かったグラフィックエンジンから取り除いた変数一覧
	/*
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファビューポート
	ID3D11DeviceContext*	m_pImmediateContext = NULL;					//即時コンテキスト
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	D3D11_FEATURE_DATA_THREADING m_featureDataThreading;
	*/
};
