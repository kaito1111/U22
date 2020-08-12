/// <summary>
/// ディレクションライト
/// </summary>
/// <remarks>カメラのカラー、方向、生データを返す程度のクラス</remarks>

#pragma once

#include "blight.h"
#include "LightBase.h"

namespace myEngine {
	class DirectionLight : public LightBase
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		DirectionLight();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~DirectionLight();
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool StartSub();
		/// <summary>
		/// 更新
		/// </summary>
		void Update() override final;
		/// <summary>
		/// ライトの方向設定
		/// </summary>
		/// <param name="direction">ライトの方向</param>
		void SetDirection(const CVector3& direction);
		/// <summary>
		/// カメラの向きを取得
		/// </summary>
		/// <returns>カメラの向き</returns>
		const CVector3& GetDirection() const
		{
			return m_lig.direction;
		}
		/// <summary>
		/// カメラのカラーを設定
		/// </summary>
		/// <param name="color">カメラのカラー</param>
		void SetColor(const CVector4& color);
		/// <summary>
		/// ディレクションライトの生データ
		/// </summary>
		/// <returns>生データ</returns>
		SDirectionLight& GetRawData()
		{
			return m_lig;
		}

	private:
		SDirectionLight		m_lig;			//ディレクションライト
	};
}
