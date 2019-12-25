/// <summary>
/// エンジン
/// </summary>
/// <remarks>
/// 各機能のインスタンスの取得とか、
/// エンジンを起動させる準備とかいろいろ
/// </remarks>

#pragma once
#include "graphics/GraphicsEngine.h"

namespace myEngine {
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		/// <summary>
		/// エンジンのシングルトンです。
		/// </summary>
		/// <returns>エンジン</returns>
		/// <remarks>
		/// エンジンのインスタンスは一個しか作れないようになってます。
		/// </remarks>
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

	private:
		GraphicsEngine			m_graphicsEngine;	//グラフィックエンジン
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
	/// グラフィックエンジンを取得
	/// </summary>
	/// <returns>グラフィックエンジン</returns>
	static inline GraphicsEngine& graphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
}

