/// <summary>
/// Playerのprefab
/// 1.基本的な移動処理(移動、向き)
/// 2.キャラコンによる当たり判定
/// 3.カスケードシャドウマップによるシャドウ生成
/// </summary>

#pragma once

class ShadowMap;
#include "character/CharacterController.h"

namespace myEngine {
	class DebugMan : public IGameObject
	{
	public:
		//コンストラクタ
		DebugMan();
		//デストラクタ
		~DebugMan();
		//スタート
		bool Start();
		/// <summary>
		/// アニメーションの初期化
		/// </summary>
		void AnimInit();
		//更新
		void Update();
		/// <summary>
		/// 移動処理
		/// </summary>
		void Move();
		/// <summary>
		/// PreRender
		/// <para>シャドウマップ描画</para>
		/// </summary>
		void PreRender();
		//描画
		void Draw();
	public:
		/// <summary>
		/// SampleManの位置取得
		/// </summary>
		/// <returns></returns>
		const CVector3& GetPosition()
		{
			return m_pos;
		}
	private:
		CVector3 m_pos = CVector3::Zero();				//デバッグマンの位置
		CVector3 m_scale = CVector3::One();				//デバッグマンの拡大率
		CQuaternion m_rot = CQuaternion::Identity();	//デバッグマンの回転軸
		SkinModel m_skinModel;							//デバッグマンのスキンモデル
		ShadowMap* m_shadowMap = nullptr;				//シャドウマップ
		CharacterController m_charaCon;					//キャラコン
		const float m_moveSpeed = -2.5f;				//基礎移動速度
		//アニメーション系 マジックナンバーダメ絶対
		enum EnAnimationClip {
			enAnimClip_idle,	//ひまやなぁアニメーション
			enAnimClip_walk,	//歩くのだるいわぁアニメーション
			enAnimClip_run,		//ｳｵｵｵｵｵｵｵｵアニメーション
			enAnimClip_Num		//アニメーションの数
		};
		Animation m_animation;							//アニメーション
		AnimationClip m_animClip[enAnimClip_Num];		//アニメーションクリップ

	};
}
