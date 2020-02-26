/// <summary>
/// ライトの管理者
/// </summary>

#pragma once

#include "Light.h"
#include "GPUBuffer/StructuredBuffer.h"
#include "GPUBuffer/ConstantBuffer.h"

namespace myEngine {
	//ディレクションライト
	class DirectionLight;
	//ライトの基底クラス
	class LightBase;
	/// <summary>
	/// ライトの管理者
	/// </summary>
	/// <remarks>
	/// 1.ライトのバッファーの初期化
	/// 2.ライトのリスト管理
	/// </remarks>
	class LightManager
	{
	public:
		LightManager();
		~LightManager();
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();
		/// <summary>
		/// ライトをリストに追加
		/// </summary>
		/// <param name="light">追加するライト</param>
		void AddLight(LightBase* light);
		/// <summary>
		/// ライトをリストから除外
		/// </summary>
		/// <param name="light">除外するライト</param>
		void RemoveLight(LightBase* light);
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// 描画設定
		/// </summary>
		void Render();
		/// <summary>
		/// 描画終了
		/// </summary>
		void EndRender();
	private:
		/// <summary>
		/// ディレクションライトのストラクチャーバッファーを初期化
		/// <para>LightManager内でしか使ってないのでprivate</para>
		/// </summary>
		void InitDirectionLightStructuredBuffer();
	private:
		static const int MAX_DIRECTION_LIGHT = 8;		//ディレクションライトの最大個数
		struct SLightParam {
			CVector3 eyePos;			//視点の位置
			int numDirectionLight;		//ディレクションライトの数
			CVector4	screenParam;	//スクリーンパラメーター
		};
	public:
		SLightParam							m_lightParam;		//ライトの情報		
		ConstantBuffer						m_lightParamCB;		//GPUで使用するライト用のパラメータ定数バッファ
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];	//ディレクションライトの生データ
		std::list<DirectionLight*>			m_directionLights;	//ディレクションライトのリスト
		StructuredBuffer					m_directionLightSB;	//ディレクションライトのストラクチャーバッファー
	};
}
