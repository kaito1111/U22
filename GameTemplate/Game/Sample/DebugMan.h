/// <summary>
/// Playerのprefab
/// 1.基本的な移動処理
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
		/// <summary>
		/// コンストラクタ
		/// </summary>
		DebugMan();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~DebugMan();
		/// <summary>
		/// スタート
		/// </summary>
		bool Start() { return true; };
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// Drawより早い描画
		/// </summary>
		void PreRender();
		/// <summary>
		/// 描画
		/// </summary>
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
		CVector3 m_moveSpeed = CVector3::Zero();		//移動速度
	};
}
