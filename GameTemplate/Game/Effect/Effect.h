/// <summary>
/// エフェクト
/// 描画はエフェクトエンジンがまとまて行う。	
/// </summary>

#pragma once
#include "GameObject/IGameObject.h"

namespace myEngine {
	class Effect : public IGameObject
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Effect();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~Effect();
		/// <summary>
		/// 明示的な解放
		/// </summary>
		void Release();
		/// <summary>
		/// エフェクトの再生
		/// <para>float x y z を引数で渡したほうがいいかも？</para>
		/// </summary>
		/// <param name="filePath">再生するエフェクトのパス</param>
		void Play(const wchar_t* filePath);
		/// <summary>
		/// 座標の設定
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 回転の設定
		/// </summary>
		/// <param name="rot">回転</param>
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="scale">拡大率</param>
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// エフェクトが再生中かの判定
		/// </summary>
		/// <returns>再生中/停止中</returns>
		bool IsPlay() const
		{
			return EffectEngineObj().GetEffekseerManager()->GetShown(m_handle);
		}
		/// <summary>
		/// 更新
		/// </summary>
		void Update(); //override;
	private:
		Effekseer::Effect*				m_effect = nullptr;			//エフェクト
		Effekseer::Handle				m_handle = -1;				//ハンドル
		CVector3 m_position =			CVector3::Zero();			//座標
		CQuaternion m_rotation =		CQuaternion::Identity();	//回転
		CVector3 m_scale =				CVector3::One();			//拡大率
	};
}

