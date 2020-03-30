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