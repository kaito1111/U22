/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//シャドウマップ
Texture2D<float4> shadowMap : register(t1);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;
	float4x4 mLightProj;
	int isShadowReciever;
};

static const int NUM_DIRECTION_LIG = 4;

/*
	ライト用定数バッファ 
*/
cbuffer LightCb : register(b0) {
	float3		Direction[NUM_DIRECTION_LIG];	//カメラの方向
	float4		Color[NUM_DIRECTION_LIG];		//カラー
	float3		eyePos;							//視点の座標
	bool		active = true;					//アクティブ
	float		specPow/*[NUM_DIRECTION_LIG]*/;		//鏡面反射の絞り 最後に書いて！
};	

/*
	シャドウマップ用の定数バッファ
*/
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;
};

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
	psInput.worldPos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	
	psInput.Position = pos;

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
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);

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
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	//ディレクションライトの拡散反射光を計算する。
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


	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4( 0.5f, 0.5f, 0.5f, 1.0f);
}

