/// <summary>
/// エンジン
/// </summary>
/// <remarks>
/// 各機能のインスタンスの取得とか、
/// エンジンを起動させる準備とかいろいろ
/// </remarks>

#pragma once
#include "graphics/GraphicsEngine.h"
#include "sound/soundengine.h"
#include "Effect/CEffectEngine.h"
#include "util/tkStopwatch.h"
#include "graphics/2D/Font.h"
#include "TwoP_Pad.h"

namespace myEngine {
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		/// <summary>
		/// スタート
		/// </summary>
		/// <returns></returns>
		bool Start();
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// エンジン終了処理
		/// </summary>
		void Final();
		/// <summary>
		/// エンジンのシングルトンです。
		/// </summary>
		static CEngine& GetInstance()
		{
			//シングルトンの処理
			static CEngine* instance = nullptr;
			if (instance == nullptr) {
				instance = new CEngine;
			}
			return *instance;
		}
		/// <summary>
		/// グラフィックエンジンの取得
		/// </summary>
		/// <returns>グラフィックエンジン</returns>
		GraphicsEngine& GetGraphicsEngine()
		{
			return m_graphicsEngine;
		}
		/// <summary>
		/// サウンドエンジンの取得
		/// </summary>
		/// <returns></returns>
		SoundEngine& GetSoundEngine()
		{
			return m_soundEngine;
		}
		/// <summary>
		/// エフェクトエンジン取得。
		/// </summary>
		/// <returns></returns>
		CEffectEngine& GetEffectEngine()
		{
			return m_effectEngine;
		}
		/// <summary>
		/// ストップウォッチ取得。
		/// </summary>
		/// <returns></returns>
		CStopwatch& getSW()
		{
			return m_sw;
		}
		/// <summary>
		/// 2つのパッドの取得。
		/// </summary>
		/// <returns></returns>
		TwoP_Pad& GetTwoP_Pad()
		{
			return m_twoP_Pad;
		}
	private:
		//エンジン関連
		GraphicsEngine			m_graphicsEngine;		//グラフィックエンジン
		SoundEngine				m_soundEngine;			//サウンドエンジン
		CEffectEngine			m_effectEngine;			//エフェクトエンジン
		//共通
		CStopwatch				m_sw;					//ストップウォッチ
		TwoP_Pad				m_twoP_Pad;				//２プレイヤーのパッドの管理オブジェクト(にしたいﾖﾃｲ）
	private:
		//fps表示関連
		float					m_timeTotal = 0;		//合計時間。
		float					m_fps = 0;				//FPS。
		std::unique_ptr<CFont>	m_font;					//フォント。

	};		

	/// <summary>
	/// エンジンを取得
	/// </summary>
	/// <returns>エンジン</returns>
	static inline CEngine& Engine()
	{
		return CEngine::GetInstance();
	}
	/// <summary>
	/// エンジンからグラフィックエンジンを取得
	/// </summary>
	/// <returns>グラフィックエンジン</returns>
	static inline GraphicsEngine& graphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
	/// <summary>
	/// エンジンからサウンドエンジンの取得
	/// </summary>
	/// <returns></returns>
	static inline SoundEngine& soundEngine()
	{
		return Engine().GetSoundEngine();
	}
	/// <summary>
	/// エフェクトエンジン取得
	/// </summary>
	/// <returns></returns>
	static inline CEffectEngine& EffectEngineObj()
	{
		return Engine().GetEffectEngine();
	}
}

