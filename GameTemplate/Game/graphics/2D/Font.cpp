#include "stdafx.h"
#include "Font.h"

namespace myEngine {
	CFont::CFont()
	{
		//初期化ぁ～
		m_spriteBatch = graphicsEngine().GetSpriteBatch();
		m_spriteFont = graphicsEngine().GetSpriteFont();
		GraphicsEngine& ge = GraphicsEngine();
		//拡大度。とりあえず、111で固定
		m_scaleMat.MakeScaling(
			{1.0f, 1.0f, 1.0f}
		);
	}

	CFont::~CFont()
	{
	}

	void CFont::Begin()
	{
		//現在のレンダーステートを保存
		graphicsEngine().PushRenderState();
		//描画設定。
		m_spriteBatch->Begin(
			DirectX::SpriteSortMode_Deferred,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			m_scaleMat
		);
	}

	void CFont::End()
	{
		//描画終了。
		m_spriteBatch->End();
		//レンダーステートをもとに戻す。
		graphicsEngine().SetRenderState();
	}

	void CFont::Draw(
		wchar_t const* text,
		const CVector2& pos,
		const CVector4& color,
		float rotation,
		float scale,
		CVector2 pivot
	)
	{
		if (text == nullptr) {
			//なにもないから、なにもせん！
			return;
		}
		//UV座標の解説はGameProg参照。
		//Unityのpivotに合わせる
		pivot.y = 1.0f - pivot.y;
		DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
		//座標計算
		CVector2 position = pos;
		position.x += FRAME_BUFFER_W;
		position.y = -position.y + FRAME_BUFFER_H;
		//描画
		m_spriteFont->DrawString(
			m_spriteBatch,
			text,
			position.vec,
			color,
			rotation,
			DirectX::XMFLOAT2(pivot.x, pivot.y),
			scale
		);
	}
}