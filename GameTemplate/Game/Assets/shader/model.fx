/*!
 * @brief	モデルシェーダー。
 */

#include "modelCB.h"
#include "modelStruct.h"

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//シャドウテクスチャ
Texture2D<float4>g_shadowMap0:register(t2);
Texture2D<float4>g_shadowMap1:register(t3);
Texture2D<float4>g_shadowMap2:register(t4);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////

/*
	使用するシャドウマップの番号を取得
*/
int GetCascadeIndex(float zInView)
{
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		if (zInView < shadowAreaDepthInViewSapce[i]) {
			return i;
		}
	}
	return 0;
}

float CalcShadowPercent(Texture2D<float4> tex, float2 uv, float depth)
{
	//シャドウマップの深度情報
	float shadow_val = tex.Sample(g_sampler, uv).r;
	//return shadow_val;
	//深度テスト
	if (depth > shadow_val.r + 0.01f) {
		//手前にあるのでシャドウを落とす。
		return 1.0f;
	}
	return 0.0f;
}

float CalcShadow(float3 wp, float zInView)
{
	float shadow = 0.0f;
	//シャドウレシーバーだった
	if (isShadowReciever == 1)
	{
		//shadow = 1.0f;
		//影を落とす。
		//使用するシャドウマップの番号を取得。
		int cascadeIndex = GetCascadeIndex(zInView);
		//ライト座標軸に変換
		float4 posInLVP = mul(mLVP[cascadeIndex], float4(wp, 1.0f));
		//ライト座標系での深度値を計算。
		posInLVP.xyz /= posInLVP.w;

		//深度値を取得
		float depth = posInLVP.z;
		
		//uv座標に変換.
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);

		//どのシャドウマップか
		if (cascadeIndex == 0) {
			//影を落とすかどうかの判定。
			shadow = CalcShadowPercent(g_shadowMap0, shadowMapUV, depth);
		}
		else if (cascadeIndex == 1) {
			//影を落とすかどうかの判定。
			shadow = CalcShadowPercent(g_shadowMap1, shadowMapUV, depth);
		}
		else if (cascadeIndex == 2) {
			shadow = CalcShadowPercent(g_shadowMap2, shadowMapUV, depth);
		}
	}

	return shadow;
}

/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	
	//ワールド座標計算
	float4 pos = mul(mWorld, In.Position);
	//ワールド座標系
	psInput.worldPos = pos;
	//カメラ座標系計算
	pos = mul(mView, pos);
	//カメラ座標系
	psInput.posInview = pos;
	//スクリーン座標系計算
	pos = mul(mProj, pos);
	
	//ピクセルシェーダーにプロジェクション座標を渡す
	psInput.Position = pos;

	//シャドウレシーバー（影を受け取るオブジェクト）かどうかの判定
	if (isShadowReciever == 1) {
		//シャドウレシーバーだった
		//ビュー行列に変換
		psInput.posInLVP = mul(mLightView, float4 (psInput.worldPos, 1.0f));
		//プロジェクション行列に変換
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	//ピクセルシェーダーに渡す
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	//スキニングした、ワールド座標。
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	//スキニングされた、ワールド座標。
	psInput.SkiningPos = pos;

	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	//スクリーン座標系に変換
	pos = mul(mView, pos);
	psInput.posInview = pos;
	pos = mul(mProj, pos);
	//スクリーン座標
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(g_sampler, In.TexCoord);
	
	//ライトの影響度
	float3 lig = 0.0f;

	//デイレクションライトの計算
	for (int i = 0; i < NUM_DIRECTION_LIG; i++)
	{
		if (active == true) {
			//ディレクションライトが有効
			lig += max(0.0f, dot(In.Normal * -1.0f, Direction[i])) * Color[i];
		}
		else if(active == false){
			//ディレクションライトが無効
			return albedoColor;
		}
	}

	//鏡面反射の計算
	for (int i = 0; i < NUM_DIRECTION_LIG; i++)
	{
		if (specPow/*[i]*/ >= 1.0f) 
		{
			//鏡面反射反射させる
			{
				//ライトを当てる面から視点に伸びるベクトル計算
				float3 toEyeDir = normalize(eyePos - In.worldPos);
				//反射ベクトル
				float3 reflectV = -toEyeDir + 2 * dot(In.Normal, toEyeDir)* In.Normal;
				//反射ベクトルとディレクションライトの内積からスペキュラの強さ計算
				float3 t = max(0.0f, dot(-Direction[i], reflectV));

				if (Color[i].x != 0 && Color[i].y != 0 && Color[i].z != 0) {
					//カラーがあるなら
					//スペキュラ計算  pow(x,y) = xのy乗
					float3 spec = pow(t, specPow/*[i]*/) * Color[i].xyz;
					//ligに加算
					lig += spec;
				}
			}
		}
	}

	//calcShadowした後にreturn 1.0fが帰ってきたらシャドウが落ちる。
	float f = 0.0f;
	//シャドウを落とす計算。
	f = CalcShadow(In.worldPos, In.posInview.z);
	if (f == 1.0f)
	{
		//影が落ちているのでライトの明かりを弱める。
		lig *= 0.5f;
	}
	//lig *= f;

	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	//finalColor.x = f;
	return finalColor;
}
//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4( 0.5f, 0.5f, 0.5f, 1.0f);
}

/*
	スキンなしシャドウマップ生成用の頂点シェーダー
*/
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/*
	スキンありシャドウマップ生成用の頂点シェーダー
*/
PSInput_ShadowMap VSMain_ShadowMapSkin(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}

	//pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/*
	ピクセルシェーダーのエントリ関数
*/
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す
	float z = In.Position.z / In.Position.w;
    return z;
}

