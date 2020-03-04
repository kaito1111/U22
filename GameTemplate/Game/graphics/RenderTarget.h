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
	/// <returns></returns>
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}

private:
	ID3D11Texture2D*			m_renderTargetTex;		//レンダーターゲットとなるテクスチャ
	ID3D11RenderTargetView*		m_renderTargetView;		//レンダーターゲットビュー
	ID3D11RenderTargetView*		m_oldRenderTargetView;	//バックアップ用のレンダーターゲットビュー
	ID3D11ShaderResourceView*	m_renderTargetSRV;		//レンダーターゲットのSRV
	ID3D11Texture2D*			m_depthStencilTex;		//デプスステンシルとなるテクスチャ
	ID3D11DepthStencilView*		m_depthStencilView;		//デプスステンシルビュー
	ID3D11DepthStencilView*		m_oldDepthStencilView;	//バックアップ用のデプスステンシルビュー
};

