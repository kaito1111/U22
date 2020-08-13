#pragma once

namespace myEngine {
	class CFont
	{
	public:
		CFont();
		~CFont();
		/// <summary>
		/// フォントを設定。
		/// </summary>
		/// <param name="font"></param>
		void SetFont(DirectX::SpriteFont* font)
		{
			m_spriteFont = font;
		}
		/// <summary>
		/// 描画開始処理。
		/// </summary>
		void Begin();
		/// <summary>
		/// 描画終了処理。
		/// </summary>
		void End();
		/// <summary>
		/// 描画。
		/// </summary>
		/// <param name="text">表示するテキスト</param>
		/// <param name="pos">位置</param>
		/// <param name="color">色</param>
		/// <param name="rotation">回転</param>
		/// <param name="scale">大きさ</param>
		/// <param name="pivot">基点</param>
		void Draw(
			wchar_t const* text,
			const CVector2& pos,
			const CVector4& color = CVector4::White(),
			float rotation = 0.0f,
			float scale = 1.0f,
			CVector2 pivot = {0.5f, 0.5f}
		);

	private:
		DirectX::SpriteBatch*		m_spriteBatch = nullptr;	//スプライトバッチ。
		DirectX::SpriteFont*		m_spriteFont = nullptr;		//スプライトフォント。
		ID3D11RasterizerState*		m_RasState = nullptr;		//バックアップラスタライザー。
		ID3D11BlendState*			m_BleState = nullptr;		//バックアップブレンドステート。
		ID3D11DepthStencilState*	m_DepthState = nullptr;		//デプスステンシルステート。
		CMatrix m_scaleMat;									//スプライトのスケール。
	};
}

