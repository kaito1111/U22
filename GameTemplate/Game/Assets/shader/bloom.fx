/// <summary>
/// ブルーム用のシェーダー
/// </summary>

/// <summary>
/// 頂点シェーダーの入力
/// </summary>
struct VSInput {
	float4 pos : SV_Position;	//頂点座標
	float2 uv : TEXCOORD0;		//頂点UV座標
};

/// <summary>
/// ピクセルシェーダーの入力
/// </summary>
struct PSInput {
	float4 pos : SV_POSITION;	//ピクセル座標
	float2 uv : TEXCOORD0;		//ピクセルUV座標
};

/// <summary>
/// 頂点シェーダー
/// </summary>
/// <remarks>
/// ピクセルシェーダーに座標を渡す。
/// </remarks>
PSInput VSMain(VSInput In)
{
	//ピクセルシェーダー
	PSInput psIn;		
	//ピクセルシェーダーを頂点シェーダーの座標に移動
	psIn.pos = In.pos;	
	//ピクセルシェーダーを頂点シェーダーのUV座標に移動
	psIn.uv = In.uv;
	return psIn;
}

Texture2D<float4> sceneTexture : register(t0);	//シーンテクスチャ
sampler Sampler : register(s0);

/// <summary>----------
/// 輝度抽出用
/// </summary>---------

/// <summary>
/// 輝度抽出用のピクセルシェーダー
/// </summary>
float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
	//シーンテクスチャをフェッチ(取り出し）
	float4 color = sceneTexture.Sample(Sampler, In.uv);
	//輝度抽出用の計算
	float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	//clip(t) tが負の数ならばピクセルキル（以降の処理をなくす）
	//輝度が1.0以下ならピクセルキル
	clip(t - 1.001f);
	//追加分だけ乗算
	color.xyz *= (t - 1.0f);
	//α値を設定
	color.a = 1.0f;
	return color;
}

/// <summary>-------------
/// ブラー
/// </summary>------------