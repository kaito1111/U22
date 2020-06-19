/// <summary>
/// シャドウマップ
/// </summary>
/// <remarks>
/// サンプルコードはDebugManクラスとStageクラスのコンストラクタを確認
/// </remarks>


#pragma once

#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "SamplerState.h"

namespace myEngine {
	class ShadowMap 
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		ShadowMap();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~ShadowMap();

		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// 削除
		/// </summary>
		void Release();

		/// <summary>
		/// ライトビュー行列を取得。
		/// </summary>
		/// <returns></returns>
		CMatrix GetLightViewMatirx() const
		{
			return m_lightViewMatrix;
		}

		/// <summary>
		/// ライトプロジェクション行列を取得
		/// </summary>
		/// <returns></returns>
		CMatrix GetLightProjMatirx() const
		{
			return m_lightProjMatirx;
		}

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// <para>更新(ライトカメラの注視点を指定するバージョン。)</para>
		/// </summary>
		/// <remarks>
		/// ライトビュー行列や、ライトプロジェクション行列を更新。
		/// 毎フレーム呼び出すこと。
		/// </remarks>
		/// <param name="lightCameraPos">ライトカメラの視点の座標</param>
		/// <param name="lightCameraTarget">ライトカメラの注視点の座標</param>
		void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);

		/// <summary>
		/// ライトの座標計算
		/// <para></para>
		/// </summary>
		/// <remarks>
		/// 視錐台の中心座標を先に計算しておく必要があります。
		/// シャドウマップの回数分回すこと。
		/// コードの詳細はカスケードシャドウ資料のCalcLightPosition.png参照。
		/// </remarks>
		/// <param name="lightHeight">ライトの高さ</param>
		/// <param name="viewFrustomCenterPosition">視錐台の中心座標</param>
		/// <returns>ライトの座標</returns>
		CVector3 CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition);
		
		/// /// <summary>
		/// ライト
		/// </summary>
		void UpdateFromLightTarget();

		/// <summary>
		/// 更新（ライトカメラの向きを指定するバージョン。
		/// </summary>
		/// <remarks>
		/// ライトビュー行列、ライトプロジェクション行列を更新。
		/// UpdateFromLightTargetかUpdateFromLightDirectionどちらかを
		/// 毎フレーム呼び出すこと。
		/// </remarks>
		/// <param name="lightCameraPos">ライトカメラの視点の座標</param>
		/// <param name="lightDir">ライトカメラの注視点の座標</param>
		void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);

		/// <summary>
		/// <para>シャドウマップにシャドウキャスターをレンダリング。</para>
		/// <para>この関数を呼び出すと、シャドウキャスターのリストはクリアされます。</para>
		/// <para>毎フレーム呼び出すこと。</para>
		/// <para>★★超重要★★</para>
		/// <para>この関数を呼び出す前にBginRender,呼び出した後EndRenderを呼ぶこと</para>
		/// <para>★★超重要★★</para>
		/// </summary>
		/// <remarks>
		/// シャドウマップに描画されるシャドウキャスターは
		/// RegistShadowCaster関数を使用して登録されたキャスターのみです。
		/// </remarks>
		void RenderToShadowMap();

		/// <summary>
		/// シャドウキャスター(影を生成するオブジェクト）の登録
		/// <para>常に影を生成する場合毎フレーム呼び出すこと。</para>
		/// </summary>
		/// <remarks>
		/// この関数を使って、登録されたキャスターが
		/// シャドウマップに描画されます。
		/// 登録されたキャスターのリストはRenderToShadowMapを呼び出したら
		/// クリアされます。
		/// </remarks>
		/// <param name="shadowCaster"></param>
		void RegistShdowCaster(SkinModel* shadowCaster)
		{
			m_shadowCasters.push_back(shadowCaster);
		}

		/// <summary>
		/// 描画設定のバックアップ
		/// </summary>
		/// <remarks>
		/// 1.レンダーターゲットビューをバックアップ。
		/// 2.深度ステンシルビューをバックアップ。
		/// 3.ビューポートをバックアップ。
		/// </remarks>
		void BiginRender();

		/// <summary>
		/// 元の描画設定に戻す
		/// </summary>
		void EndRender();


		/// <summary>
		/// シャドウマップのSRVを取得
		/// </summary>
		/// <returns></returns>
		ID3D11ShaderResourceView* GetShadowMapSRV()
		{
			return m_shadowMapRT.GetRenderTargetSRV();
		}

	private:
		//カスケードシャドウ実装用変数//
		
		/// <summary>
		/// こいつの中身いじったらShadowCbも変更すること
		/// </summary>
		struct SShadowCb {
			CMatrix mLVP[NUM_SHADOW_MAP];						//ライトビュープロジェクション行列
			CVector4 texOffset[NUM_SHADOW_MAP];					//Pivotみたいな感じ？
			float shadowAreaDepthInViewSpace[NUM_SHADOW_MAP];	//カメラ空間での影を落とすエリアの深度テーブル
		};

		float m_lightHieght = 2000.0f;									//ライトの高さ
		int shadowMapWidth = 2048;												//シャドウマップの幅
		int shadowMapHeight = 2048;											//シャドウマップの高さ
		RenderTarget m_KshadowMapRT[NUM_SHADOW_MAP]; 					//シャドウマップを書き込むレンダーターゲット
		CMatrix m_LVPMatrix[NUM_SHADOW_MAP];							//ライトビュープロジェクション行列
		SShadowCb m_shadowCbEntity;										//送る用
		ConstantBuffer m_shadowCb;										//シャドウ用定数バッファ
		SamplerState m_fetchShadowMapSampler;							//シャドウマップをフェッチするときに使用するサンプラ-
		CVector3 m_lightDirection = CVector3::Down();					//ライトの方向

		//ここまでカスケードシャドウ//

		CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点
		CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点
		CMatrix m_lightViewMatrix;							//ライトビュー行列
		CMatrix	m_lightProjMatirx;							//ライトプロジェクション行列
		RenderTarget m_shadowMapRT;							//シャドウマップ描画用のレンダリングターゲット
		std::vector<SkinModel*> m_shadowCasters;			//シャドウキャスターの配列
		ID3D11RenderTargetView* oldRenderTargetView;		//バックアップ用レンダーターゲットビュー
		ID3D11DepthStencilView* oldDepthStencilView;		//バックアップ用深度ステンシルビュー
		D3D11_VIEWPORT oldViewports;						//バックアップ用ビューポート
		unsigned int viewport = 1;							//ビューポート
	};

}


