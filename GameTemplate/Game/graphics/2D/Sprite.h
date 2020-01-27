/// <summary>
/// スプライト
/// </summary>

#include "graphics/Primitive.h"

#pragma once

namespace myEngine {
	class Sprite
	{
	public:
		static const CVector2	DEFAULT_PIVOT;		//ピボット
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Sprite();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~Sprite();
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="tex">テクスチャ</param>
		/// <param name="w">幅</param>
		/// <param name="h">高さ</param>
		void Init(ID3D11ShaderResourceView* tex, float w, float h);
		/// <summary>
		/// テクスチャの設定
		/// </summary>
		/// <param name="tex">テクスチャ</param>
		void SetTextrue(ID3D11ShaderResourceView* tex)
		{
			m_textureSRV = tex;
		}
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="trans">平行移動</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大</param>
		/// <param name="pivot">基点</param>
		/// <remarks>
		/// pivotの挙動
		/// (0.5,0.5)中心	(0.0,0.0)左下	(1.0,1.0)右上
		/// UnityのuGUIと一緒
		/// </remarks>
		void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="viewMatrix">カメラの位置</param>
		/// <param name="projMatrix">画角とか</param>
		/// <param name="w">透明度（書かなくてもOK）</param>
		void Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix, const float w = 1.0f);

	private:
		//構造体型スプライト用の定数バッファ
		struct SSpriteCB {
			CMatrix WVP;			//ワールドビュープロジェクション行列
			CVector4 m_mulColor;	//乗算カラー
		};
		CVector3					m_position = CVector3::Zero();			//座標
		CQuaternion					m_rotation = CQuaternion::Identity();	//回転
		CVector3					m_scale = CVector3::Zero();				//スケール
		CMatrix						m_world = CMatrix::Identity();			//ワールド行列
		Primitive					m_primitive;							//プリミティブ
		Shader						m_ps;									//ピクセルシェーダー
		Shader						m_vs;									//頂点シェーダー
		ConstantBuffer				m_cb;									//定数バッファ
		CVector4					m_mulColor = CVector4::White();			//乗算カラー								//透明度
		ID3D11ShaderResourceView*	m_textureSRV = nullptr;					//テクスチャ
		ID3D11SamplerState*			SamplerState;							//サンプルステート
		ID3D11BlendState*			BlendState;								//ブレンドステート
		bool				m_isInited = false;						//初期化フラグ
		CVector2			m_size = CVector2::Zero();				//サイズ(大きさ)
	};
}



