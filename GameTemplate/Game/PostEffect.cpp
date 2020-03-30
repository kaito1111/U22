#include "stdafx.h"
#include "PostEffect.h"

namespace myEngine {
	PostEffect::PostEffect()
	{
		//フルスクリーン描画のための四角形プリミティブを初期化。
		InitFullScreenQuadPrimitive();
	}

	PostEffect::~PostEffect()
	{
		if (m_vertexBuffer != nullptr) {
			m_vertexBuffer->Release();
		}
	}

	void PostEffect::Update()
	{
		m_bloom.Update();
	}

	void PostEffect::Draw()
	{
		m_bloom.Draw(*this);
	}

	struct SVertex
	{
		float position[4];		//テクスチャを張り付ける頂点座標
		float uv[2];			//UV座標。テクスチャ座標
	};

	void PostEffect::InitFullScreenQuadPrimitive()
	{
		//頂点バッファを初期化
		SVertex vertex[4] = {
			//頂点1(左下
			{
				//頂点座標
				-1.0f, -1.0f, 0.0f, 1.0f,
				//テクスチャ座標
				0.0f, 1.0f
			},
			//頂点2(右下
			{
				//頂点座標
				1.0f, -1.0f, 0.0f, 1.0f,
				//テクスチャ座標
				1.0f, 1.0f
			},
			//頂点3(左上
			{
				//頂点座標
				-1.0f, 1.0f, 0.0f, 1.0f,
				//テクスチャ座標
				0.0f, 0.0f
			},
			//頂点4(右上
			{
				//頂点座標
				1.0f, 1.0f, 0.0f, 1.0f,
				//テクスチャ座標
				1.0f, 0.0f
			}
		};

		//バッファーの設定
		D3D11_BUFFER_DESC bd;
		//0ｼｮｷｶｱｱｱｱｱｱｱｱｱｱ
		ZeroMemory(&bd, sizeof(bd));
		//バッファーの読み込み、書き込み設定
		bd.Usage = D3D11_USAGE_DEFAULT;
		//頂点バッファのサイズ
		bd.ByteWidth = sizeof(vertex);
		//なんのバッファとして登録するんじゃ？　頂点バッファじゃ
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//サブリソースでデータの初期化
		//なんでしてるのかわからない。Sampleの方でNULL渡してもエラーはでんかった。
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertex;

		//頂点バッファの作成
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
	}

	void PostEffect::DrawFullScreenQuadPrimitive(Shader& vsShader, Shader& psShader)
	{
		auto dc = g_graphicsEngine->GetD3DDeviceContext();
		//トポロジー(どうやって描画するか的な）をトライアングルストリップに設定
		dc->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//頂点サイズ
		unsigned int vertexSize = sizeof(SVertex);
		//間隔
		unsigned int offset = 0;
		//輝度抽出用のシェーダー設定
		dc->VSSetShader(
			(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
		);
		dc->PSSetShader(
			(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
		);
		//レイアウト設定
		dc->IASetInputLayout(vsShader.GetInputLayout());
		//頂点バッファの設定
		dc->IAGetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
		//描画
		dc->Draw(4, 0);
	}
}