/// <summary>
/// �u���[���p�̃V�F�[�_�[
/// </summary>

/// <summary>
/// ���_�V�F�[�_�[�̓���
/// </summary>
struct VSInput {
	float4 pos : SV_Position;	//���_���W
	float2 uv : TEXCOORD0;		//���_UV���W
};

/// <summary>
/// �s�N�Z���V�F�[�_�[�̓���
/// </summary>
struct PSInput {
	float4 pos : SV_POSITION;	//�s�N�Z�����W
	float2 uv : TEXCOORD0;		//�s�N�Z��UV���W
};

/// <summary>
/// ���_�V�F�[�_�[
/// </summary>
/// <remarks>
/// �s�N�Z���V�F�[�_�[�ɍ��W��n���B
/// </remarks>
PSInput VSMain(VSInput In)
{
	//�s�N�Z���V�F�[�_�[
	PSInput psIn;		
	//�s�N�Z���V�F�[�_�[�𒸓_�V�F�[�_�[�̍��W�Ɉړ�
	psIn.pos = In.pos;	
	//�s�N�Z���V�F�[�_�[�𒸓_�V�F�[�_�[��UV���W�Ɉړ�
	psIn.uv = In.uv;
	return psIn;
}

Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`��
sampler Sampler : register(s0);

/// <summary>----------
/// �P�x���o�p
/// </summary>---------

/// <summary>
/// �P�x���o�p�̃s�N�Z���V�F�[�_�[
/// </summary>
/// <para>PSInput</para>
float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
	//�V�[���e�N�X�`�����t�F�b�`(���o���j
	float4 color = sceneTexture.Sample(Sampler, In.uv);
	//�P�x���o�p�̌v�Z
	float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	//clip(t) t�����̐��Ȃ�΃s�N�Z���L���i�ȍ~�̏������Ȃ����j
	//�P�x��1.0�ȉ��Ȃ�s�N�Z���L��
	clip(t - 1.001f);
	//�ǉ���������Z
	color.xyz *= (t - 1.0f);
	//���l��ݒ�
	color.a = 1.0f;
	return color;
}

/// <summary>-------------
/// �u���[
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

//�P�x���o�e�N�X�`��
Texture2D<float4> luminanceTexture : register(t0);

/// <summary>
/// �u���[�p�̒萔�o�b�t�@
/// </summary>
cbuffer CBBlur : register(b0)
{
	float4 offset;			//�I�t�Z�b�g
	float4 weight[2];		//�d��
}

/// <summary>
/// X�u���[�̒��_�V�F�[�_�[
/// </summary>
/// <para>VSInput�̕ϐ���In���g���Ďg�p�ł���B</para>
PS_BlurInput VSXBlur(VSInput In)
{
	//�e�N�X�`���̏��
	float2 texSize;			//�e�N�X�`���T�C�Y(UV
	float level;			//�}�b�v�̐��H
	

	//�P�x�e�N�X�`���̃T�C�Y���擾
	//GetDimansions(minimapLevel, wight, height, minimapCount);
	luminanceTexture.GetDimensions(0, texSize.x, texSize.y, level);

	//�u���[�̒�`
	PS_BlurInput Out;
	//�e�N�X�`���̈ʒu����
	Out.pos = In.pos;
	//UV���W����
	float2 tex = In.uv;

	//UV���W��X�ڂ����v�Z
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
	//�l�𑗂�
	return Out;
}

/// <summary>
/// Y�u���[���_�V�F�[�_�[
/// </summary>
/// <para>VSInput�̕ϐ���In���g���Ďg�p�ł���B</para>
PS_BlurInput VSYBlur(VSInput In)
{
	//�P�x�e�N�X�`���̏��
	float2 texSize;		//UV���W
	float level;		//�}�b�v�̐�

	//�e�N�X�`���̏����擾
	luminanceTexture.GetDimensions(0, texSize.x, texSize.y, level);

	//�u���[�̃s�N�Z�����
	PS_BlurInput Out;

	//�u���[�̃s�N�Z���ɍ��W��n���B
	Out.pos = In.pos;
	//�e�N�X�`��������
	float2 tex = In.uv;

	//UV���W��Y�ڂ����v�Z
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
/// �u���[�̃s�N�Z���V�F�[�_�[
/// </summary>
float4 PSBlur(PS_BlurInput In) : SV_Target0
{
	//�J���[
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

//�ŏI�u���[�e�N�X�`��
Texture2D<float4> finalBlurTexture : register(t0);

float4 PSFinal(PSInput In) : SV_Target0
{
	float4 color = finalBlurTexture.Sample(Sampler, In.uv);
	return color;
}