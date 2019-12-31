#include "stdafx.h"
#include "Sprite.h"
#include "GPUView/ShaderResourceView.h"
#include "graphics/Shader.h"
#include "RenderContext.h"
#include "math/Matrix.h"

namespace myEngine {
	namespace {
		struct SSimpleVertex
		{
			CVector4 pos;
			CVector2 tex;
		};
	}
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
	void Sprite::Init(ShaderResourceView& tex, float w, float h)
	{
		//シェーダーをロード
		m_ps.Load("shader/sprite.fx", "PSMain", Shader::EnType::PS);
		m_vs.Load("shader/sprite.fx", "VSMain", Shader::EnType::VS);
		//大きさ
		m_size.x = w;
		m_size.y = h;
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

		m_primitive.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			IndexBuffer::enIndexType_16,
			indices
		);
		m_textureSRV = &tex;
		m_cb.Create(nullptr, sizeof(SSpriteCB));
		m_isInited = true;
	}
	void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
	{
		if (m_isInited == false) {
			//初期化されてない
			return;
		}
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
		m_world = mPivotTrans * mScale;
		m_world = m_world * mRot;
		m_world = m_world * mTrans;
	}

	void Sprite::Draw(RenderContext& rc, const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{
		if (m_isInited == false) {
			//未初期化
			return;
		}
		if (m_textureSRV == nullptr) {
			//SRVがない
			//tkEngineはここでエラーメッセージ
			return;
		}
		SSpriteCB cb;
		cb.WVP = m_world;
		cb.WVP = cb.WVP * viewMatrix;
		cb.WVP = cb.WVP * projMatrix;
		cb.m_mulColor = m_mulColor;

		rc.UpdateSubResourse(m_cb, &cb);
		rc.VSSetConstantBuffer(0, m_cb);
		rc.PSSetConstantBuffer(0, m_cb);
		rc.PSSetShaderResource(0, *m_textureSRV);
		rc.PSSetShader(m_ps);
		rc.VSSetShader(m_vs);
		m_primitive.Draw(rc);
	}
}


