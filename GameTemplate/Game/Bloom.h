#pragma once

namespace myEngine {
	/// <summary>
	/// ブルーム
	/// </summary>
	class Bloom : public IGameObject 
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Bloom();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~Bloom();
		/// <summary>
		/// レンダーターゲットの初期化
		/// </summary>
		void InitRenderTarget();
		/// <summary>
		/// シェーダーの初期化
		/// </summary>
		void InitShader();
		/// <summary>
		/// アルファブレンドステートの初期化
		/// </summary>
		void InitAlphaBlendState();
		/// <summary>
		/// サンプラーステートの初期化
		/// </summary>
		void InitSamplerState();
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	private:
		ID3D11SamplerState* m_samplerState = nullptr;		//サンプラーステート
		ID3D11BlendState* m_disableBlendState = nullptr;	//αを無効にするブレンドステート
		ID3D11BlendState* m_finalBlendState = nullptr;		//最終合成用ブレンドステート
	private:
		RenderTarget m_luminaceRT;		//輝度抽出用のレンダリングターゲット
		RenderTarget m_downSamplingRT;	//ブラーをかけるためのダウンサンプリング
		Shader m_vs;					//そのままの頂点シェーダー
		Shader m_psLuminance;			//輝度抽出用のピクセルシェーダー
		Shader m_vsXBlur;				//Xブラー用頂点シェーダー
		Shader m_vsYBlur;				//Yブラー用頂点シェーダー
		Shader m_psBlur;				//ブラー用ピクセルシェーダー
		Shader m_psFinal;				//最終合成用のピクセルシェーダー


	};
}
