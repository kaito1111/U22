#pragma once

class RenderTarget
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~RenderTarget();

	/// <summary>
	/// レンダリングターゲットの作成
	/// </summary>
	/// <param name="w">テクスチャの幅</param>
	/// <param name="h">テクスチャの高さ</param>
	/// <param name="texFormat">テクスチャのフォーマット</param>
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);

	/// <summary>
	/// 解放処理
	/// </summary>
	void Release();

	/// <summary>
	/// レンダーターゲットとデプスステンシルのクリア
	/// </summary>
	/// <param name="clearColor">クリアカラー</param>
	void ClearRenderTarget(float* clearColor);

	/// <summary>
	/// レンダーターゲットビュの取得
	/// </summary>
	/// <returns>レンダーターゲットビュー</returns>
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}

	/// <summary>
	/// デプスステンシルビューの取得
	/// </summary>
	/// <returns>デプスステンシルビュー</returns>
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}

	/// <summary>
	/// レンダリングターゲットのSRVを取得
	/// </summary>
	/// <returns>レンダリングターゲットのSRV</returns>
	ID3D11ShaderResourceView*& GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}

	/// <summary>
	/// ビューポートの取得
	/// </summary>
	/// <returns>ビューポート</returns>
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
	/// <summary>
	/// 横幅の取得
	/// </summary>
	/// <returns></returns>
	float GetWidth()
	{
		return m_width;
	}
	/// <summary>
	/// 高さの取得
	/// </summary>
	/// <returns></returns>
	float GetHeight()
	{
		return m_height;
	}

private:
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//レンダーターゲットとなるテクスチャ
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//レンダーターゲットビュー
	ID3D11RenderTargetView*		m_oldRenderTargetView = nullptr;	//バックアップ用のレンダーターゲットビュー
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//レンダーターゲットのSRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//デプスステンシルとなるテクスチャ
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//デプスステンシルビュー
	ID3D11DepthStencilView*		m_oldDepthStencilView = nullptr;	//バックアップ用のデプスステンシルビュー
	D3D11_VIEWPORT				m_viewport;				//ビューポート
	float m_width = 0;									//レンダリングターゲットの幅
	float m_height = 0;									//レンダリングターゲットの高さ
};

