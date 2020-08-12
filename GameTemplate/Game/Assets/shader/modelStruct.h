/*
	モデル関連の構造体。
	ここを変えたら、model.fxの処理も変えること。
*/

/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;			//頂点座標。
	float3 Normal : NORMAL;					//法線。
	float3 Tangent : TANGENT;				//接ベクトル。
	float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
	float4 Position : SV_Position;			//頂点座標。
	float3 Normal : NORMAL;					//法線。
	float2 TexCoord : TEXCOORD0;			//UV座標。
	float3 Tangent : TANGENT;				//接ベクトル。
	uint4  Indices : BLENDINDICES0;			//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
	float4 Weights : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput {
	float4 Position : SV_Position;		//ピクセル座標
	float3 Normal : NORMAL;				//法線
	float3 Tangent : TANGENT;			//接ベクトル
	float2 TexCoord : TEXCOORD0;		//UV座標
	float3 worldPos : TEXCOORD1;		//ワールド座標
	float4 posInLVP : TEXCOORD2;		//ライトビュー座標
	float4 SkiningPos : TEXCOORD3;		//スキニングした、ワールド座標。
	float4 posInview : TEXCOORD4;		//ビュー座標
};

/*
	シャドウマップ用のピクセルシェーダーへの入力構造体
*/
struct PSInput_ShadowMap {
	float4 Position : SV_POSITION;	//座標
};