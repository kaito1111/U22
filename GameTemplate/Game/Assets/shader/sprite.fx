/*!
 * @brief	スプライト用のシェーダー。
 */

cbuffer cb : register(b0){
	float4x4 mvp;		//ワールドビュープロジェクション行列。
	float4 mulColor;	//乗算カラー。
};
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
	//float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	//float monoColor = color.x * 0.29900 + color.b * 0.58700 + color.b * 0.11400;
	//color.r = monoColor;
	//color.g = monoColor;
	//color.b = monoColor;
	//return color;
}