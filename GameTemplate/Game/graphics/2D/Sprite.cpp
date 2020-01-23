#include "stdafx.h"
#include "Sprite.h"
#include "GPUView/ShaderResourceView.h"
#include "graphics/Shader.h"
#include "math/Matrix.h"

namespace myEngine {
	struct SSimpleVertex
	{
		CVector4 pos;
		CVector2 tex;
	};
	//ピボットの初期化
	const CVector2 Sprite::DEFAULT_PIVOT = { 0.5f,0.5f };
	Sprite::Sprite()
	{
	}
	Sprite::~Sprite()
	{
	}
	/// <summary>
	/// SRVのロード
	/// </summary>
	/// <remarks>
	/// SSimpleVertexは2Dが入る四角形の初期化？
	/// </remarks>
	void Sprite::Init(ID3D11ShaderResourceView* tex, float w, float h)
	{
		//シェーダーをロード
		m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
		m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//大きさ
		m_size.x = w / 1280.0f;
		m_size.y = h / 720.0f;
		float halfW = w * 0.5f;
		float halfH = h * 0.5f;
		//頂点バッファのソースデータ
		SSimpleVertex vertices[] =
		{
			{
				CVector4(-halfW, -halfH, 0.0f, 1.0f),
				CVector2(0.0f,1.0f),
			},
			{
				CVector4(halfW, -halfH, 0.0f, 1.0f),
				CVector2(1.0f, 1.0f),
			},
			{
				CVector4(-halfW, halfH, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(halfW, halfH, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}
		};
		short indices[] = { 0,1,2,3 };
		//プリミティブの作成
		m_primitive.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			IndexBuffer::enIndexType_16,
			indices
		);

		//引数で入ってきたテクスチャの代入
		m_textureSRV = tex;
		//定数バッファの作成
		m_cb.Create(nullptr, sizeof(SSpriteCB));
		
		//サンプラーステートの作成
		D3D11_SAMPLER_DESC dese;
		//サンプラーステート関連の初期化処理
		ZeroMemory(&dese, sizeof(dese));
		dese.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//サンプラーステートの作成処理
		//ここでSpriteクラスのサンプラーステートにポインタが入るよ！
		g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&dese, &SamplerState);


		//ブレンドステートの設定
		CD3D11_DEFAULT drfault;
		CD3D11_BLEND_DESC BLEND_DETE(drfault);
		BLEND_DETE.RenderTarget[0].BlendEnable = true;
		//2個を一回で初期化してるよ 同じ値なのでできる！
		BLEND_DETE.RenderTarget[0].BlendOp = BLEND_DETE.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].DestBlend = BLEND_DETE.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].SrcBlend = BLEND_DETE.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;

		//ブレンドステートの作成 & 初期化
		auto Device = g_graphicsEngine->GetD3DDevice(); 
		Device->CreateBlendState(&BLEND_DETE, &BlendState);
	}
	void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
	{
		//if (m_isInited == false) {
		//	//初期化されてない
		//	return;
		//}
		//ピボットを考慮に入れた平行移動行列を作成
		//ピボットは真ん中が0,0,0、左上が-1,-1、右下が1.0,1.0になるように
		CVector2 localPivot = pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//画像のハーフサイズを求める
		CVector2 halfSize = m_size;
		halfSize.x *= 0.5f;
		halfSize.y *= 0.5f;
		CMatrix mPivotTrans;

		mPivotTrans.MakeTranslation(
			{halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f}
		);
		CMatrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(trans);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		m_world = mPivotTrans * mScale;
		m_world = m_world * mRot;
		m_world = m_world * mTrans;
	}

	void Sprite::Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{

		CMatrix view;
		CMatrix proj;
		view.MakeLookAt(
			{ 0.0f,0.0f,-1.0f },
			{ 0.0f,0.0f,0.0f },
			CVector3::Up()
		);

		proj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 2.0f);

		ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		/*
		g_graphicsEngine->GetD3DDeviceContext()->OMSetBlendState(kjl, nullptr, 0xFFFFFFFF);
		MemoryBarrier();
		
		ID3D11DepthStencilState* kkkkk;
		D3D11_DEPTH_STENCIL_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		desc.StencilEnable = false;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		pd3d->CreateDepthStencilState(&desc, &kkkkk);

		g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(kkkkk, 0);
		*/
		/*
		if (m_isInited == false) {
			//未初期化
			return;
		}
		*/
		if (m_textureSRV == nullptr) {
			//SRVがない
			//tkEngineはここでエラーメッセージ
			return;
		}
		//定数バッファ
		SSpriteCB cb;
		//プロジェクション行列を乗算
		cb.WVP = m_world;
		cb.WVP = cb.WVP * view;
		cb.WVP = cb.WVP * proj;
		//乗算カラーの代入
		cb.m_mulColor = m_mulColor;

		d3dDeviceContext->UpdateSubresource(m_cb.GetBody(), 0, NULL, &cb, 0, 0);
		d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb.GetBody());
		d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb.GetBody());
		d3dDeviceContext->VSSetShaderResources(0, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShaderResources(0, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
		d3dDeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
		d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());
		//rc.UpdateSubResourse(m_cb, &cb);
		//rc.VSSetConstantBuffer(0, m_cb);
		//rc.PSSetConstantBuffer(0, m_cb);
		//g_graphicsEngine->GetD3DDeviceContext()->VSSetShaderResources(0, 1, &m_textureSRV->GetBody());
		//g_graphicsEngine->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_textureSRV->GetBody());
		////rc.PSSetShaderResource(0, *m_textureSRV);
		//rc.PSSetShader(m_ps);
		//rc.VSSetShader(m_vs);

		//g_graphicsEngine->GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
		g_graphicsEngine->GetD3DDeviceContext()->VSSetSamplers(0, 1, &SamplerState);
		g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers(0, 1, &SamplerState);

		//ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//g_graphicsEngine->GetD3DDeviceContext()->OMSetBlendState(kjl, nullptr, 0xFFFFFFFF);

		m_primitive.Draw(*d3dDeviceContext);
	}
}