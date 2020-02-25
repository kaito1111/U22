/// <summary>
/// ディレクションライト
/// </summary>

#pragma once
#include "GameObject/IGameObject.h"

namespace myEngine {

	const int NUM_DIRECTION_LIG = 4;	//平行ライトの数 ここの値変えたらInitDirectionLightも増やすこと

	/// <summary>
	/// ディレクションライト
	/// </summary>
	struct SDirectionLight
	{
		CVector4 direction[NUM_DIRECTION_LIG];	//ライトの方向
		CVector4 color[NUM_DIRECTION_LIG];		//ライトのカラー
		int		 active[NUM_DIRECTION_LIG];		//0ならFalse, 1ならTrue
	};

	/// <summary>
	/// ライトの設定とディレクションライトの初期化
	/// </summary>
	class DirectionLight : public IGameObject
	{
	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// 解放処理
		/// </summary>
		void Release();
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
		/// <summary>
		/// 描画設定
		/// </summary>
		void Render();
		/// <summary>
		/// 定数バッファの作成
		/// </summary>
		void CreateLightCB();
		/// <summary>
		/// ディレクションライトの初期化
		/// </summary>
		void InitDirectionLight();
	private:
		ID3D11Buffer*	m_lightCb = nullptr;	//ライトの定数バッファ
		SDirectionLight	m_dirLight;				//ディレクションライト
	};


}
