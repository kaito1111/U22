#pragma once

namespace myEngine {
	class PostEffect;
	/// <summary>
	/// ブルーム
	/// </summary>
	class Bloom 
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
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// 描画
		/// </summary>
		void Draw(PostEffect& postEffect);
	private:
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
		/// 定数バッファの初期化
		/// </summary>
		void InitConstantBuffer();
		/// <summary>
		/// サンプラーステートの初期化
		/// </summary>
		void InitSamplerState();
	private:
		static const int NUM_WEIGHTS = 8;	//重みの数
		/// <summary>
		/// ブラー用のパラメータバッファ
		/// <para>これを変更したら、Shader/bloom.fxのCBBlurの中身も変更するように</para>
		/// </summary>
		struct SBlurParam {
			CVector4 offset;			//間隔
			float weights[NUM_WEIGHTS];	//重み
		};
		ID3D11SamplerState* m_samplerState = nullptr;		//サンプラーステート
		ID3D11BlendState* m_disableBlendState = nullptr;	//αを無効にするブレンドステート
		ID3D11BlendState* m_finalBlendState = nullptr;		//最終合成用ブレンドステート
	private:
		RenderTarget m_luminaceRT;		//輝度抽出用のレンダリングターゲット
		RenderTarget m_downSamplingRT[2];	//ブラーをかけるためのダウンサンプリング
		Shader m_vs;					//そのままの頂点シェーダー
		Shader m_psLuminance;			//輝度抽出用のピクセルシェーダー
		Shader m_vsXBlur;				//Xブラー用頂点シェーダー
		Shader m_vsYBlur;				//Yブラー用頂点シェーダー
		Shader m_psBlur;				//ブラー用ピクセルシェーダー
		Shader m_psFinal;				//最終合成用のピクセルシェーダー
		ID3D11Buffer* m_blurParamCB = nullptr;	//ブラーパラメーター用の定数バッファ

	};
}
