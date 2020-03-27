/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */

cbuffer cb : register(b0){
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float4 mulColor;	//��Z�J���[�B
};
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
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
	//���ʂ̃X�v���C�g�̃J���[
	float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;

	//���m�N��2D�i���Ɏg���ˁ[�񂗂��j
	{
		//float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
		//float monoColor = color.x * 0.29900 + color.b * 0.58700 + color.b * 0.11400;
		//color.r = monoColor;
		//color.g = monoColor;
		//color.b = monoColor;
	}

	//�R���g���X�g����2D�i���Ɏg���ˁ[�񂗂��j
	{
		//float akarusa = max(color.r, color.g);
		//akarusa = max(akarusa, color.b);
		////���邢�Ƃ��͂���ɖ��邭
		//if (akarusa > 0.5f) {
		//	color.r = min(1.0f, color.r * 1.5f);
		//	color.g = min(1.0f, color.g * 1.5f);
		//	color.b = min(1.0f, color.b * 1.5f);
		//}
		////�Â��Ƃ��͂���ɈÂ�
		//else {
		//	color.r *= 0.5f;
		//	color.g *= 0.5f;
		//	color.b *= 0.5f;
		//}
	}

	//�Z�s�A��2D�i���Ɏg���ˁ[�񂗂��j
	{
		//color.r = color.r * 0.393 + color.g * 0.769 + color.b * 0.189;
		//color.g = color.r * 0.349 + color.g * 0.686 + color.b * 0.168;
		//color.b = color.r * 0.272 + color.g * 0.534 + color.b * 0.131;
	}
	
	return color;

}