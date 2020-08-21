/// <summary>
/// フォントレンダー。
/// </summary>
/// <remarks>
/// GameObjectManager下で管理する、フォントのラッパークラス。
/// Drawのタイミングが、エンジンのデフォルト呼び出しでいいならこいつを使う。
/// 違う場合は、標準のフォントクラスを使う事。
/// </remarks>

#pragma once

namespace myEngine {
	class CFontRender : public IGameObject
	{
	public:
		/// <summary>
		/// フォント設定。
		/// </summary>
		void SetFont(DirectX::SpriteFont* font)
		{
			m_font.SetFont(font);
		}
		/// <summary>
		/// テキストを設定。
		/// <para>おもいでぇ。</para>
		/// <para>基本Unsafe版使えると思うから、使ってな。</para>
		/// </summary>
		/// <param name="text">テキスト。</param>
		void SetText(const wchar_t* text)
		{
			if (wcscmp(m_text.c_str(), text) != 0) {
				//文字列に変更があった。
				//ここでコピーが発生する？
				m_text = text;
			}
		}
		/// <summary>
		/// アンセーフ版、SetText。
		/// <para>使う前に、とりあえず説明(remarks)みてね。</para>
		/// </summary>
		/// <remarks>
		/// メンバ変数で引数に渡すの定義したら、まずバグらないはず。
		/// ローカル変数で引数に渡すの定義したら、バグるよ。
		/// 意味わからない場合は、通常版使ってください。
		/// メンバ変数に書いておかしくなったら、教えてください。
		/// </remarks>
		/// <param name="text"></param>
		void SetTextUnsafe(const wchar_t* text)
		{
			//コピーが発生しない。
			m_textUnsafe = text;
		}
		/// <summary>
		/// フォントを表示する座標設定。
		/// <para>画面中央が0,0</para>
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(const CVector2& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// フォントの色を設定。
		/// </summary>
		/// <param name="color">カラー</param>
		void SetColor(const CVector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// フォントの色を設定。
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const CVector4& color)
		{
			m_color = color;
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(float rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// 拡大率。
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// ピボットの設定。
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
	private:
		void PostRender() override;
	private:
		CFont			m_font;								//フォント。
		std::wstring	m_text;								//テキスト。
		const wchar_t*	m_textUnsafe;						//アンセーフテキスト。
		CVector2		m_position = CVector2::Zero();		//座標。(0.0f,0.0f)で真ん中。
		CVector4		m_color = CVector4::White();		//カラー。
		float			m_rotation = 0.0f;					//回転。
		float			m_scale = 1.0f;						//スケール。
		CVector2		m_pivot = {0.5f, 0.5f};				//ピボット。
	};
}
