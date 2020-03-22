#pragma once

#include "ShadowMap.h"

namespace myEngine {
	/// <summary>
	/// ！！デバッグマン！！
	/// 能力ⅰ：シャドウマップの作成ができる。
	/// 能力ⅱ：影を出せる。
	/// </summary>
	/// <remarks>
	/// エンジンの機能追加の際など既存のPlayerとか使うのは、
	/// 気が引けるので作成。
	/// モデルも後々かえて、アニメーションも付けたい。
	/// </remarks>
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
		void Render();
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	private:
		CVector3 m_pos = CVector3::Zero();				//デバッグマンの位置
		CVector3 m_scale = CVector3::One();				//デバッグマンの拡大率
		CQuaternion m_rot = CQuaternion::Identity();	//デバッグマンの回転軸
		CVector3 m_lightCameraPosition;					//ライトカメラの視点位置
		CVector3 m_lightCameraTarget;					//ライトカメラの注視点位置
		SkinModel m_skinModel;							//デバッグマンのスキンモデル
		ShadowMap* m_shadowMap = nullptr;				//シャドウマップ
	};
}
