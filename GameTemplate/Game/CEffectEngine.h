/// <summary>
/// エフェクトの管理者
/// エフェクサー側の関数をラップ
/// </summary>

#pragma once
#include "Noncopyable.h"
#include "ResourceManager.h";

namespace myEngine {
	//エフェクト用のリソースマネージャー
	using CEffectResourceManager = TResourceManager<Effekseer::Effect>;
	class CEffectEngine : Noncopyable
	{
	public:
		CEffectEngine();
		~CEffectEngine();
		/// <summary>
		/// 解放
		/// </summary>
		void Release();
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// 描画
		/// </summary>
		void Render();
		/// <summary>
		/// エフェクトを作成。wraper
		/// </summary>
		/// <param name="filepath">エフェクトのファイルパス</param>
		/// <returns></returns>
		Effekseer::Effect* CreateEffect(const wchar_t* filepath);
		/// <summary>
		/// エフェクトの再生。wraper
		/// <para>EffectのUpdateで座標軸の変換はすること。</para>
		/// </summary>
		/// <param name="effet">再生するエフェクト</param>
		/// <returns>エフェクトのハンドル</returns>
		Effekseer::Handle Play(Effekseer::Effect* effet);
		/// <summary>
		/// エフェクトの再生を停止。
		/// </summary>
		/// <param name="handle">エフェクトのハンドル</param>
		void Stop(Effekseer::Handle handle);
		/// <summary>
		/// エフェクサーのマネージャー取得。
		/// </summary>
		/// <remarks>
		/// アドレスとポインタどっちも使うのでダブルポインタ化
		/// </remarks>
		/// <returns></returns>
		Effekseer::Manager*& GetEffekseerManager() 
		{
			return *&m_manager;
		}
		/// <summary>
		/// エフェクサーのレンダラー取得。
		/// </summary>
		/// <returns></returns>
		EffekseerRenderer::Renderer*& GetEffekseerRenderer() 
		{
			return *&m_effekseerRenderer;
		}
		/// <summary>
		/// エフェクトリソースマネージャーの取得。
		/// </summary>
		/// <returns></returns>
		CEffectResourceManager& GetEffectResourceManager()
		{
			return m_effectResourceManager;
		}
	private:
		EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;			//エフェクサーレンダー
		Effekseer::Manager* m_manager = nullptr;							//エフェクトマネジャー
		CEffectResourceManager m_effectResourceManager;						//エフェクトリソースマネジャー
	};
}

