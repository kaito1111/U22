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
	/// SSimpleVertexは2Dが入る四角形の初期化
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
		//UVWが1を超えるときのテクスチャの処理をどうするか
		//D3D11_TEXTURE_ADDRESS_WRAPは普通に繰り返し　補足...ミラーとかもあったよ
		dese.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		dese.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		//縮小、拡大、サンプリングに線形補間を使用
		dese.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		//サンプラーステートの作成処理
		//ここでSpriteクラスのサンプラーステートにポインタが入るよ！
		Engine().GetGraphicsEngine().GetD3DDevice()->CreateSamplerState(&dese, &SamplerState);


		//ブレンドステートの設定
		CD3D11_DEFAULT drfault;
		CD3D11_BLEND_DESC BLEND_DETE(drfault);
		BLEND_DETE.RenderTarget[0].BlendEnable = true;
		BLEND_DETE.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		BLEND_DETE.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BLEND_DETE.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		
		//ブレンドステートの作成 & 初期化
		auto Device = Engine().GetGraphicsEngine().GetD3DDevice();
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

	void Sprite::Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix, const float w)
	{
		
		//CMatrix view;
		//CMatrix proj;
		//view.MakeLookAt(
		//	{ 0.0f,0.0f,-1.0f },
		//	{ 0.0f,0.0f,0.0f },
		//	CVector3::Up()
		//);

		//proj.MakeOrthoProjectionMatrix(1280.0f, 720.0f, 0.1f, 2.0f);

		ID3D11DeviceContext* d3dDeviceContext = Engine().GetGraphicsEngine().GetD3DDeviceContext();

		/*
		if (m_isInited == false) {
			//未初期化
			return;
		}
		*/
		if (m_textureSRV == nullptr) {
			//SRVがない
			//SRVのポインタ確認してね
			throw;
			return;
		}
		//定数バッファ
		SSpriteCB cb;
		//プロジェクション行列を乗算
		cb.WVP = m_world;
		cb.WVP = cb.WVP * viewMatrix;
		cb.WVP = cb.WVP * projMatrix;
		//乗算カラーの代入 + 透明度の乗算
		cb.m_mulColor = m_mulColor * w;

		d3dDeviceContext->UpdateSubresource(m_cb.GetBody(), 0, NULL, &cb, 0, 0);

		d3dDeviceContext->VSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb.GetBody());
		d3dDeviceContext->PSSetConstantBuffers(enSkinModelCBReg_VSPS, 1, &m_cb.GetBody());
		d3dDeviceContext->VSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_textureSRV);
		d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
		d3dDeviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
		d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());

		//サンプラーステートのセット
		Engine().GetGraphicsEngine().GetD3DDeviceContext()->VSSetSamplers(0, 1, &SamplerState);
		Engine().GetGraphicsEngine().GetD3DDeviceContext()->PSSetSamplers(0, 1, &SamplerState);

		m_primitive.Draw(*d3dDeviceContext);
	}
}