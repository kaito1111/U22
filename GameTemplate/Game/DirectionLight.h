/// <summary>
/// ディレクションライト
/// </summary>
/// <remarks>
/// IGameObjectを継承していないので、
/// LightManagerで対応した関数を作成して、呼び出してください。
/// </remarks>

#pragma once
#include "GameObject/IGameObject.h"

namespace myEngine {

	const int NUM_DIRECTION_LIG = 4;	//平行ライトの数 ここの値変えたらInitDirectionLightも増やすこと

	/// <summary>
	/// ディレクションライト
	/// </summary>
	struct SDirectionLight
	{
		CVector4	direction[NUM_DIRECTION_LIG];	//ライトの方向
		CVector4	color[NUM_DIRECTION_LIG];		//ライトのカラー
		CVector3	eyePos;							//視点の座標	
		bool		active;							//0ならFalse, 1ならTrue
		float		specPow/*[NUM_DIRECTION_LIG]*/;		//鏡面反射の絞り
	};

	/// <summary>
	/// ライトの設定とディレクションライトの初期化
	/// </summary>
	class DirectionLight 
	{
	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// 16の倍数に切り上げ
		/// </summary>
		int Raundup(int n)
		{
			return (((n - 1) / 16) + 1) * 16;
		}
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

		void SetColor(CVector4 color, int i = 0 ) {
			m_dirLight.color[i] = color;
		}
		void SetColor(CVector3 color, int i = 0) {
			CVector4 Color = { color.x,color.y,color.z,1.0f };
			m_dirLight.color[i] = Color;
		}
	private:
		ID3D11Buffer*		m_lightCb = nullptr;	//ライトの定数バッファ
		SDirectionLight		m_dirLight;				//ディレクションライト
	};
}
