#pragma once
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
		void Update() {};
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

		friend class CGameObjectManager;
	protected:
		GameObjPrio		m_priority;		//優先度
		bool			m_isStart;		//Startフラグ
		bool			m_isDead;		//死亡フラグ
		bool			m_isActive;		//Activeフラグ
		unsigned int	m_tags = 0;		//タグ
		unsigned int	m_nameKey = 0;	//名前キー
	};
}


