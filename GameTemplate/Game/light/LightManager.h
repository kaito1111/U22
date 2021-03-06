/// <summary>
/// ライトマネージャー
/// </summary>
/// <remarks>
/// 本体を渡してるだけです
/// グラフィックエンジンからライトをもって持ってきたかったけど
/// 参照で渡すと本体ができるのが早すて、ディレクションライトのD3D系でエラーでる、
/// ポインタはグラフィックエンジンでCreateしてるわけじゃないので現実的じゃない
/// 以上を踏まえて作成
/// </remarks>

#pragma once

#include "DirectionLight.h"

namespace myEngine
{
	class LightManager : public IGameObject
	{
	public:
		~LightManager()
		{
			int a = 0;
		}
		/// <summary>
		/// ディレクションライトの取得
		/// </summary>
		/// <returns></returns>
		myEngine::DirectionLight& GetDirLig()
		{
			return m_dirLig;
		}

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	private:
		std::list<DirectionLight> m_directionLights;	//ディレクションライトのリスト
		myEngine::DirectionLight m_dirLig;				//ディレクションライト
	};
}
