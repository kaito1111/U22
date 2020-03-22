/// <summary>
/// シャドウマップ
/// </summary>
/// <remarks>
/// サンプルコードはDebugManクラスとStageクラスのコンストラクタを確認
/// </remarks>


#pragma once

#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"

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


