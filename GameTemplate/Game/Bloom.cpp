#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

namespace myEngine {

	Bloom::Bloom()
	{
		//各レンダーターゲットの初期化
		InitRenderTarget();
		//シェーダーの初期化
		InitShader();
		//アルファブレンドステート
		InitAlphaBlendState();
		//サンプラーステート
		InitSamplerState();
	}

	Bloom::~Bloom()
	{

	}

	void Bloom::InitRenderTarget()
	{
		//輝度抽出用RT
		//16Bit浮動小数点バッファを使用
		m_luminaceRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);
	}
	
	void Bloom::InitShader()
	{
		//そのままの頂点シェーダーをロード
		m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
		//輝度を抽出した頂点シェーダーのロード
		m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
		//Xブラー用の頂点シェーダー
		//m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", Shader::EnType::VS);
		////Yブラー用の頂点シェーダー
		//m_vsYBlur.Load("Aseets/shader/bloom.fx", "VSYBlur", Shader::EnType::VS);
		////ブラー用ピクセルシェーダー
		//m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", Shader::EnType::PS);
		////最終合成用ピクセルシェーダー
		//m_psFinal.Load("Assets/Shader/bloom.fx", "PSFinal", Shader::EnType::PS);
	}

	void Bloom::InitAlphaBlendState()
	{
		//デフォルト設定
		CD3D11_DEFAULT defalut;
		//デフォルトで初期化
		CD3D11_BLEND_DESC blendDesc(defalut);
		
		//デバイスの取得
		auto dv = g_graphicsEngine->GetD3DDevice();

		//αを無効にするブレンドステートを作成
		dv->CreateBlendState(&blendDesc, &m_disableBlendState);

		//最終合成用ブレンドステートの作成
		//最終合成は加算合成。
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		//最終合成ブレンドステートを作成
		dv->CreateBlendState(&blendDesc, &m_finalBlendState);
	}

	void Bloom::InitConstantBuffer()
	{
		//wwwよくよく考えたらCBクラス使えばCreateだけでよかった件www
		//バッファーの設定
		D3D11_BUFFER_DESC desc;
		//0初期化
		ZeroMemory(&desc, sizeof(desc));
		//読み取り、書き込み方法
		desc.Usage = D3D11_USAGE_DEFAULT;
		//定数バッファのサイズ、16バイトアライメントに切り上げ
		desc.ByteWidth = (((sizeof(SBlurParam) - 1) / 16) + 1) * 16;
		//定数バッファとしてバインド
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//CPUアクセスしない
		desc.CPUAccessFlags = 0;
		//作成
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_blurParamCB);
	}

	void Bloom::InitSamplerState()
	{
		//設定
		D3D11_SAMPLER_DESC desc;
		//リセット
		ZeroMemory(&desc, sizeof(desc));
		//テクスチャの貼り方 UVW範囲外は0.0か1.0
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		//縮小、拡大、サンプリングに線形補間使用
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//作成
		g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	}

	void Bloom::Update()
	{

	}

	void Bloom::Draw(PostEffect& postEfferct)
	{
		//デバコン取得
		auto dc = g_graphicsEngine->GetD3DDeviceContext();

		dc->PSGetSamplers(0, 1, &m_samplerState);

		//バックアップ
		g_graphicsEngine->oldTarget();

		//サンプラーステートのセット
		dc->PSSetSamplers(0, 1, &m_samplerState);
		
		//輝度抽出
		{
			//αブレンドを無効のする
			float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
			dc->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

			//輝度抽出用のレンダーターゲットに変更 ChangeRenderTargetの引数dcいらねぇよなぁ！？
			g_graphicsEngine->ChangeRenderTarget(dc, &m_luminaceRT, m_luminaceRT.GetViewport());

			//レンダーターゲットのクリア
			float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };
			m_luminaceRT.ClearRenderTarget(clearColor);

			//シーンをテクスチャに。
			auto mainRTTexSRV = g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV();
			dc->PSSetShaderResources(0, 1, &mainRTTexSRV);

			//フルスクリーン描画
			postEfferct.DrawFullScreenQuadPrimitive(m_vs, m_psLuminance);
		}
		
		//ターゲットをもとに戻す
		g_graphicsEngine->PostRenderTarget();
	}
}
