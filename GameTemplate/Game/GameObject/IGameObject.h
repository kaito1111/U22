#pragma once
#include "graphics/RenderContext.h"

/// <summary>
/// ゲームオブジェクトの基底クラス
/// オブジェクトマネージャーの関数を使う場合は継承してね！！
/// </summary>


namespace myEngine {
	class GameObjectManager;
	//名前変更ししてるだけ
	typedef unsigned char	GameObjPrio;
	class IGameObject
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false)
		{
		};
		/// <summary>
		/// デストラクタ
		/// </summary>
		/// <remarks>
		/// virtualは定義してるだけです、処理は派生クラスに書いてください
		/// </remarks>
		virtual ~IGameObject()
		{
		};
		/// <summary>
		/// 描画設定
		/// </summary>
		virtual void Render()
		{
		}
		/// <summary>
		/// レンダー関数が実行された後で呼ばれる描画処理
		/// </summary>
		/// <remarks>
		/// 機能が追加されたときに追記します
		/// </remarks>
		/// <param name="rc">レンダーコンテキスト</param>
		virtual void PostDraw()
		{
		}
		/// <summary>
		/// <para>Updateの直前に呼ばれる開始処理</para>
		/// <para>trueが返されると更新処理(Update)が開始されるよ</para>
		/// </summary>
		/// <returns>
		/// オブジェクトの準備が1フレームでできるならtrue、できていないならfalse
		/// </returns>
		virtual bool Start() { return true; }
		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() {};
		/// <summary>
		/// 描画処理
		/// </summary>
		virtual void Draw() {};
		/// <summary>
		/// <para>実行優先度を取得</para>
		/// </summary>
		/// <returns>
		/// 優先度
		/// </returns>
		GameObjPrio GetPriority() const
		{
			return m_priority;
		}

	public:
		/// <summary>
		/// 関数をラップしてるだけだよ
		/// 各オブジェクトの関数の処理を開始させるよ
		/// </summary>
		void PostDrawWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead)
			{
				PostDraw();
			}
		}
		void RenderWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead)
			{
				Render();
			}
		}
		void StartWrapper()
		{
			if (m_isActive && !m_isStart)
			{
				if (Start()) {
					//初期化終了
					m_isStart = true;
				}
			}
		}
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart)
			{
				Update();
			}
		}
		void DrawWrapper()
		{
			if (m_isActive && m_isStart)
			{
				Draw();
			}
		}
		friend class GameObjectManager;
	protected:
		GameObjPrio		m_priority;		//優先度
		bool			m_isStart;		//Startフラグ
		bool			m_isDead;		//死亡フラグ
		bool			m_isActive;		//Activeフラグ
		unsigned int	m_tags = 0;		//タグ
		unsigned int	m_nameKey = 0;	//名前キー
	};
}


