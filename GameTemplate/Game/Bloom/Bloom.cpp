#include "stdafx.h"
#include "Bloom.h"

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
		//定数バッファの初期化
		InitConstantBuffer();
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

		//ブラーをかけるためのダウンサンプリング用のレンダリングターゲット
		//横ブラー用を作成。
		m_downSamplingRT[0].Create(
			FRAME_BUFFER_W * 0.5f,	//横の解像度を半分に
			FRAME_BUFFER_H,
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);

		//縦ブラー
		m_downSamplingRT[1].Create(
			FRAME_BUFFER_W * 0.5f,
			FRAME_BUFFER_H * 0.5f,	//解像度を半分に
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
		m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", Shader::EnType::VS);
		////Yブラー用の頂点シェーダー
		m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", Shader::EnType::VS);
		////ブラー用ピクセルシェーダー
		m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", Shader::EnType::PS);
		////最終合成用ピクセルシェーダー
		m_psFinal.Load("Assets/Shader/bloom.fx", "PSFinal", Shader::EnType::PS);
	}

	void Bloom::InitAlphaBlendState()
	{
		//デフォルト設定
		CD3D11_DEFAULT defalut;
		//デフォルトで初期化
		CD3D11_BLEND_DESC blendDesc(defalut);
		
		//デバイスの取得
		auto dv = Engine().GetGraphicsEngine().GetD3DDevice();

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
		Engine().GetGraphicsEngine().GetD3DDevice()->CreateBuffer(&desc, NULL, &m_blurParamCB);
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
		Engine().GetGraphicsEngine().GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	}

	void Bloom::Update()
	{
		//重みの更新
		float total = 0;
		//重みの計算
		//正負の結果が一緒なので、サンプリングするテクセルの数の半分でOK！
		//重みが8→サンプリングテクセル16
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] = expf(-0.5f * (float)(i * i) / m_blurDispersion);
			total += 2.0f * m_blurParam.weights[i];
		}
		
		//規格化
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_blurParam.weights[i] /= total;
		}

	}

	void Bloom::Draw(PostEffect& postEfferct)
	{
		//デバコン取得
		auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

		//dc->PSGetSamplers(0, 1, &m_samplerState);

		//バックアップ
		Engine().GetGraphicsEngine().oldTarget();

		//サンプラーステートのセット
		dc->PSSetSamplers(0, 1, &m_samplerState);
		
		//ガウシアンフィルタは縦横ブラーを一気にかけず
		//横→縦（逆もOK）でかけるときれいにでる。
		//輝度抽出
		{
			//αブレンドを無効にする
			float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
			dc->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

			//輝度抽出用のレンダーターゲットに変更 ChangeRenderTargetの引数dcいらねぇよなぁ！？
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, &m_luminaceRT, m_luminaceRT.GetViewport());

			//レンダーターゲットのクリア
			float clearColor[] = { 0.0f,0.0f,0.0f,1.0f };
			m_luminaceRT.ClearRenderTarget(clearColor);

			//シーンをテクスチャに。
			auto mainRTTexSRV = Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV();
			dc->PSSetShaderResources(0, 1, &mainRTTexSRV);

			//フルスクリーン描画
			postEfferct.DrawFullScreenQuadPrimitive(m_vs, m_psLuminance);
		}

		//輝度を抽出したテクスチャにXブラーをかける
		{
			//Xブラー用のレンダリングターゲットに変更する。
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, &m_downSamplingRT[0], m_downSamplingRT[0].GetViewport());

			//輝度テクスチャをt0レジスタに設定
			//輝度テクスチャの取得
			auto luminanceTexSRV = m_luminaceRT.GetRenderTargetSRV();
			//頂点シェーダーにシェーダーリソースを設定
			dc->VSSetShaderResources(0, 1, &luminanceTexSRV);
			//ピクセルシェーダーにリソースを設定
			dc->PSSetShaderResources(0, 1, &luminanceTexSRV);

			//定数バッファの更新
			//横の頂点間隔
			m_blurParam.offset.x = 16.0f / m_luminaceRT.GetWidth();
			//縦の頂点間隔
			m_blurParam.offset.y = 0.0f;
			//更新
			dc->UpdateSubresource(m_blurParamCB, 0, nullptr, &m_blurParam, 0, 0);
			//ブラー用の定数バッファを設定
			dc->PSSetConstantBuffers(0, 1, &m_blurParamCB);

			//フルスクリーン描画
			postEfferct.DrawFullScreenQuadPrimitive(m_vsXBlur, m_psBlur);
		}

		//Xブラーをかけたテクスチャに、Yブラーをかける。
		{
			//Yブラー用のレンダリングターゲットに変更
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, &m_downSamplingRT[1], m_downSamplingRT[1].GetViewport());

			//Xブラーをかけたテクスチャをt0レジスタに設定
			auto xBlurSRV = m_downSamplingRT[0].GetRenderTargetSRV();
			//shader設定
			dc->VSSetShaderResources(0, 1, &xBlurSRV);
			dc->PSSetShaderResources(0, 1, &xBlurSRV);

			//定数バッファ更新
			//頂点間隔（解像度を切り替えてるイメージ
			m_blurParam.offset.x = 0.0f;
			m_blurParam.offset.y = 16.0f / m_luminaceRT.GetHeight();
			dc->UpdateSubresource(m_blurParamCB, 0, nullptr, &m_blurParam, 0, 0);

			//フルスクリーン描画
			postEfferct.DrawFullScreenQuadPrimitive(m_vsYBlur, m_psBlur);
		}

		//最後にぼかした絵を加算合成でメインレンダリングターゲットに合成して終わり
		{
			//メインレンダリングターゲットに変更
			auto mainRT = Engine().GetGraphicsEngine().GetOffScreenRenderTarget();
			Engine().GetGraphicsEngine().ChangeRenderTarget(dc, mainRT, mainRT->GetViewport());

			//XYブラーをかけたテクスチャをt0レジスタに設定
			auto srv = m_downSamplingRT[1].GetRenderTargetSRV();
			//srvを設定
			dc->PSSetShaderResources(0, 1, &srv);

			//加算合成用のブレンディングステートを設定
			float blendFactor[] = { 0.0f,0.0f,0.0f,0.0f };
			//最終合成用ブレンドステートをセット
			dc->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);

			//フルスクリーン描画
			postEfferct.DrawFullScreenQuadPrimitive(m_vs, m_psFinal);

			//ブレンドステートをもとに戻す
			dc->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
		}
		//ターゲットをもとに戻す
		Engine().GetGraphicsEngine().PostRenderTarget();
	}
}
