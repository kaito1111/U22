/// <summary>
/// ！！デバッグマン！！
/// </summary>

#pragma once

#include "ShadowMap.h"

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
		/// 描画
		/// </summary>
		void Render();
	private:
		CVector3 m_pos = CVector3::Zero();
		CVector3 m_scale = CVector3::One();
		CQuaternion m_rot = CQuaternion::Identity();
		SkinModel m_skinModel;
	};
}
