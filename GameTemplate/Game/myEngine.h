/// <summary>
/// エンジン
/// </summary>
/// <remarks>
/// 各機能のインスタンスの取得とか、
/// エンジンを起動させる準備とかいろいろ
/// </remarks>

#pragma once
#include "graphics/GraphicsEngine.h"
#include "Sound/SoundEngine.h"
#include "CEffectEngine.h"

namespace myEngine {
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
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

	private:
		GraphicsEngine			m_graphicsEngine;	//グラフィックエンジン
		SoundEngine				m_soundEngine;		//サウンドエンジン
		CEffectEngine			m_effectEngine;		//エフェクトエンジン
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

