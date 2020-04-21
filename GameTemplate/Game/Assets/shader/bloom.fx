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
/// <para>PSInput</para>
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
struct PS_BlurInput {
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};

//輝度抽出テクスチャ
Texture2D<float4> luminanceTexture : register(t0);

/// <summary>
/// ブラー用の定数バッファ
/// </summary>
cbuffer CBBlur : register(b0)
{
	float4 offset;			//オフセット
	float4 weight[2];		//重み
}

/// <summary>
/// Xブラーの頂点シェーダー
/// </summary>
/// <para>VSInputの変数がInを使って使用できる。</para>
PS_BlurInput VSXBlur(VSInput In)
{
	//テクスチャの情報
	float2 texSize;			//テクスチャサイズ(UV
	float level;			//マップの数？
	

	//輝度テクスチャのサイズを取得
	//GetDimansions(minimapLevel, wight, height, minimapCount);
	luminanceTexture.GetDimensions(0, texSize.x, texSize.y, level);

	//ブラーの定義
	PS_BlurInput Out;
	//テクスチャの位置を代入
	Out.pos = In.pos;
	//UV座標を代入
	float2 tex = In.uv;

	//UV座標のXぼかし計算
	{
		Out.tex0 = tex + float2(-1.0f / texSize.x, 0.0f);
		Out.tex1 = tex + float2(-3.0f / texSize.x, 0.0f);
		Out.tex2 = tex + float2(-5.0f / texSize.x, 0.0f);
		Out.tex3 = tex + float2(-7.0f / texSize.x, 0.0f);
		Out.tex4 = tex + float2(-9.0f / texSize.x, 0.0f);
		Out.tex5 = tex + float2(-11.0f / texSize.x, 0.0f);
		Out.tex6 = tex + float2(-13.0f / texSize.x, 0.0f);
		Out.tex7 = tex + float2(-15.0f / texSize.x, 0.0f);
	}
	//値を送る
	return Out;
}

/// <summary>
/// Yブラー頂点シェーダー
/// </summary>
/// <para>VSInputの変数がInを使って使用できる。</para>
PS_BlurInput VSYBlur(VSInput In)
{
	//輝度テクスチャの情報
	float2 texSize;		//UV座標
	float level;		//マップの数

	//テクスチャの情報を取得
	luminanceTexture.GetDimensions(0, texSize.x, texSize.y, level);

	//ブラーのピクセル情報
	PS_BlurInput Out;

	//ブラーのピクセルに座標を渡す。
	Out.pos = In.pos;
	//テクスチャ情報を代入
	float2 tex = In.uv;

	//UV座標のYぼかし計算
	{
		Out.tex0 = tex + float2(0.0f, -1.0f / texSize.y);
		Out.tex1 = tex + float2(0.0f, -3.0f / texSize.y);
		Out.tex2 = tex + float2(0.0f, -5.0f / texSize.y);
		Out.tex3 = tex + float2(0.0f, -7.0f / texSize.y);
		Out.tex4 = tex + float2(0.0f, -9.0f / texSize.y);
		Out.tex5 = tex + float2(0.0f, -11.0f / texSize.y);
		Out.tex6 = tex + float2(0.0f, -13.0f / texSize.y);
		Out.tex7 = tex + float2(0.0f, -15.0f / texSize.y);
	}
	return Out;
}

/// <summary>
/// ブラーのピクセルシェーダー
/// </summary>
float4 PSBlur(PS_BlurInput In) : SV_Target0
{
	//カラー
	float4 Color;
	Color = weight[0].x * (luminanceTexture.Sample(Sampler, In.tex0)
		+ luminanceTexture.Sample(Sampler, In.tex7 + offset));
	Color += weight[0].y * (luminanceTexture.Sample(Sampler, In.tex1)
		+ luminanceTexture.Sample(Sampler, In.tex6 + offset));
	Color += weight[0].z * (luminanceTexture.Sample(Sampler, In.tex2)
		+ luminanceTexture.Sample(Sampler, In.tex5 + offset));
	Color += weight[0].w * (luminanceTexture.Sample(Sampler, In.tex3)
		+ luminanceTexture.Sample(Sampler, In.tex4 + offset));
	Color += weight[1].x * (luminanceTexture.Sample(Sampler, In.tex4)
		+ luminanceTexture.Sample(Sampler, In.tex3 + offset));
	Color += weight[1].y * (luminanceTexture.Sample(Sampler, In.tex5)
		+ luminanceTexture.Sample(Sampler, In.tex2 + offset));
	Color += weight[1].z * (luminanceTexture.Sample(Sampler, In.tex6)
		+ luminanceTexture.Sample(Sampler, In.tex1 + offset));
	Color += weight[1].w * (luminanceTexture.Sample(Sampler, In.tex7)
		+ luminanceTexture.Sample(Sampler, In.tex0 + offset));
	
	return float4(Color.xyz, 1.0f);
}

//最終ブラーテクスチャ
Texture2D<float4> finalBlurTexture : register(t0);

float4 PSFinal(PSInput In) : SV_Target0
{
	float4 color = finalBlurTexture.Sample(Sampler, In.uv);
	return color;
}