﻿#include "stdafx.h"
#include "GraphicsEngine.h"


GraphicsEngine::GraphicsEngine()
{
}


GraphicsEngine::~GraphicsEngine()
{
	Release();
}

void GraphicsEngine::BegineRender()
{
	float ClearColor[4] = { 0.5f
		, 0.5f, 0.5f, 1.0f 
	}; //red,green,blue,alpha
	//描き込み先をバックバッファにする。
	m_pd3dDeviceContext->OMSetRenderTargets(1, &m_backBuffer, m_depthStencilView);
	//バックバッファを灰色で塗りつぶす。
	m_pd3dDeviceContext->ClearRenderTargetView(m_backBuffer, ClearColor);
	m_pd3dDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
}

void GraphicsEngine::EndRender()
{
	//バックバッファとフロントバッファを入れ替える。
	m_pSwapChain->Present(0, 0);
}
void GraphicsEngine::Release()
{
	if (m_rasterizerState != NULL) {
		m_rasterizerState->Release();
		m_rasterizerState = NULL;
	}
	if (m_depthStencil != NULL) {
		m_depthStencil->Release();
		m_depthStencil = NULL;
	}
	if (m_depthStencilView != NULL) {
		m_depthStencilView->Release();
		m_depthStencilView = NULL;
	}
	if (m_backBuffer != NULL) {
		m_backBuffer->Release();
		m_backBuffer = NULL;
	}
	if (m_pSwapChain != NULL) {
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}
	if (m_pd3dDeviceContext != NULL) {
		m_pd3dDeviceContext->Release();
		m_pd3dDeviceContext = NULL;
	}
	if (m_pd3dDevice != NULL) {
		m_pd3dDevice->Release();
		m_pd3dDevice = NULL;
	}
	//if (m_mainRenderTarget != NULL) {
	//	m_mainRenderTarget->Release();
	//	m_mainRenderTarget = NULL;
	//}
}
#if 1
void GraphicsEngine::Init(HWND hWnd)
{
	//スワップチェインを作成するための情報を設定する。
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;									//スワップチェインのバッファ数。通常は１。
	sd.BufferDesc.Width = (UINT)FRAME_BUFFER_W;			//フレームバッファの幅。
	sd.BufferDesc.Height = (UINT)FRAME_BUFFER_H;		//フレームバッファの高さ。
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//フレームバッファのフォーマット。R8G8B8A8の32bit。
	sd.BufferDesc.RefreshRate.Numerator = 60;			//モニタのリフレッシュレート。(バックバッファとフロントバッファを入れ替えるタイミングとなる。)
	sd.BufferDesc.RefreshRate.Denominator = 1;			//２にしたら30fpsになる。1でいい。
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//サーフェスまたはリソースを出力レンダー ターゲットとして使用します。
	sd.OutputWindow = hWnd;								//出力先のウィンドウハンドル。
	sd.SampleDesc.Count = 1;							//1でいい。
	sd.SampleDesc.Quality = 0;							//MSAAなし。0でいい。
	sd.Windowed = TRUE;									//ウィンドウモード。TRUEでよい。

														//利用するDirectXの機能セット。DirectX10以上に対応しているGPUを利用可能とする。
														//この配列はD3D11CreateDeviceAndSwapChainの引数として使う。
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	//D3Dデバイスとスワップチェインを作成する。
	D3D11CreateDeviceAndSwapChain(
		NULL,											//NULLでいい。
		D3D_DRIVER_TYPE_HARDWARE,						//D3Dデバイスがアクセスするドライバーの種類。
														//基本的にD3D_DRIVER_TYPE_HARDWAREを指定すればよい。
		NULL,											//NULLでいい。
		0,												//０でいい。
		featureLevels,									//D3Dデバイスのターゲットとなる機能セットを指定する。
														//今回のサンプルはDirectX10以上をサポートするので、
														//それらを含むD3D_FEATURE_LEVELの配列を渡す。
		sizeof(featureLevels) / sizeof(featureLevels[0]),	//機能セットの数。
		D3D11_SDK_VERSION,								//使用するDirectXのバージョン。
														//D3D11_SDK_VERSIONを指定すればよい。
		&sd,											//スワップチェインを作成するための情報。
		&m_pSwapChain,									//作成したスワップチェインのアドレスの格納先。
		&m_pd3dDevice,									//作成したD3Dデバイスのアドレスの格納先。
		&m_featureLevel,								//使用される機能セットの格納先。
		&m_pd3dDeviceContext							//作成したD3Dデバイスコンテキストのアドレスの格納先。
	);

	//書き込み先になるレンダリングターゲットを作成。
	ID3D11Texture2D* pBackBuffer = NULL;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_backBuffer);
	pBackBuffer->Release();
	//深度ステンシルビューの作成。
	{
		//深度テクスチャの作成。
		D3D11_TEXTURE2D_DESC texDesc;
		ZeroMemory(&texDesc, sizeof(texDesc));
		texDesc.Width = (UINT)FRAME_BUFFER_W;
		texDesc.Height = (UINT)FRAME_BUFFER_H;
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_D32_FLOAT;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;
		m_pd3dDevice->CreateTexture2D(&texDesc, NULL, &m_depthStencil);
		//深度ステンシルビューを作成。
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = texDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		m_pd3dDevice->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);
	}
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	//ラスタライザとビューポートを初期化。
	m_pd3dDevice->CreateRasterizerState(&desc, &m_rasterizerState);
	D3D11_VIEWPORT viewport;
	viewport.Width = FRAME_BUFFER_W;
	viewport.Height = FRAME_BUFFER_H;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_pd3dDeviceContext->RSSetViewports(1, &viewport);
	{
		//ブレンド設定
		D3D11_BLEND_DESC BLEND_DETE;
		ID3D11BlendState* BlendState;
		BLEND_DETE.AlphaToCoverageEnable = false;
		BLEND_DETE.IndependentBlendEnable = false;
		BLEND_DETE.RenderTarget[0].BlendEnable = true;
		BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_pd3dDevice->CreateBlendState(&BLEND_DETE, &BlendState);
		m_pd3dDeviceContext->OMSetBlendState(BlendState, nullptr, 0xFFFFFFFF);

		MemoryBarrier();
	}
	{
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable = true;
		desc.DepthWriteMask = false ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		desc.StencilEnable = false;
		desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		desc.BackFace = desc.FrontFace;

		ID3D11DepthStencilState* depthStencilState;
		m_pd3dDevice->CreateDepthStencilState(&desc, &depthStencilState);
		m_pd3dDeviceContext->OMSetDepthStencilState(depthStencilState, 0);
		MemoryBarrier();
	}

	//Getの都合上ここでNew　tkEngineに合わせたいねぇ(願望)
	//実態をGraphicsEngineで作るとdv,dcが初期化されてないのでダメー！
	//ここ適当すぎる、後で直そう。
	{
		//ライトマネージャーの作成　※改善の余地あり
		m_ligManager = NewGO<LightManager>(0);
		//シャドウマップの作成
		m_shadowMap = new ShadowMap;
		//オフスクリーンレンダーターゲットの作成
		m_mainRenderTarget = new RenderTarget;
		m_mainRenderTarget->Create(FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R16G16B16A16_FLOAT);
		//オフスクリーンレンダリング用のスプライト作成
		m_copyMainRtToFrameBufferSprite = new Sprite;
		m_copyMainRtToFrameBufferSprite->Init(
			Engine().GetGraphicsEngine().GetOffScreenRenderTarget()->GetRenderTargetSRV(),
			FRAME_BUFFER_W,
			FRAME_BUFFER_H
		);
	}

	m_pd3dDeviceContext->RSSetViewports(1, &viewport);
	m_pd3dDeviceContext->RSSetState(m_rasterizerState);
}
#else
#endif

void GraphicsEngine::InitEffekseer()
{
}

void GraphicsEngine::ChangeRenderTarget(ID3D11DeviceContext* dc, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv, D3D11_VIEWPORT* vp)
{
	ID3D11RenderTargetView* rtTbl[] = {
		rtv
	};
	//レンダリングターゲットの切り替え。
	dc->OMSetRenderTargets(1, rtTbl, dsv);
	if (vp != nullptr) {
		//ビューポートが指定されているので、ビューポートも変更。
		dc->RSSetViewports(1, vp);
	}
}

void GraphicsEngine::ChangeRenderTarget(ID3D11DeviceContext* dc, RenderTarget* rtv, D3D11_VIEWPORT* vp)
{
	ChangeRenderTarget(
		dc,
		rtv->GetRenderTargetView(),
		rtv->GetDepthStensilView(),
		vp
	);
}

void GraphicsEngine::oldTarget()
{
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
	//バックアップの処理
	{
		//レンダーターゲットのバックアップ
		dc->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);
		//ビューポートバックアップ
		unsigned int numViewport = 1;
		dc->RSGetViewports(&numViewport, &m_frameBufferViewports);
	}
}

void GraphicsEngine::OffScreenRenderTarget()
{
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	//レンダーターゲットをセット
	Engine().GetGraphicsEngine().ChangeRenderTarget(dc, m_mainRenderTarget, &m_frameBufferViewports);

	//メインレンダリングターゲットをクリア
	float clearColor[] = { 0.5f,0.5f,0.5f,1.0f };

	m_mainRenderTarget->ClearRenderTarget(clearColor);

	//~~~~オブジェクトのレンダー処理~~~~//
}

void GraphicsEngine::PostRenderTarget()
{
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	//ターゲットをフレームバッファに
	Engine().GetGraphicsEngine().ChangeRenderTarget(
		dc,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);

	//ブレンドステート設定
	D3D11_BLEND_DESC BLEND_DETE;
	ID3D11BlendState* BlendState;
	BLEND_DETE.AlphaToCoverageEnable = false;
	BLEND_DETE.IndependentBlendEnable = false;
	BLEND_DETE.RenderTarget[0].BlendEnable = true;
	BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BLEND_DETE.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	m_pd3dDevice->CreateBlendState(&BLEND_DETE, &BlendState);
	m_pd3dDeviceContext->OMSetBlendState(BlendState, nullptr, 0xFFFFFFFF);

	//オフスクリーンレンダリング用のスプライトDraw
	//関数名的にここでかくべきじゃないけど、応急処置
	m_copyMainRtToFrameBufferSprite->Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite->Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);

	//あとでEndRenderにでも追加
	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}
