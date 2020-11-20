/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include "modelCB.h"
#include "modelStruct.h"

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
//�V���h�E�e�N�X�`��
Texture2D<float4>g_shadowMap0:register(t2);
Texture2D<float4>g_shadowMap1:register(t3);
Texture2D<float4>g_shadowMap2:register(t4);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////

/*
	�g�p����V���h�E�}�b�v�̔ԍ����擾
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
	//�V���h�E�}�b�v�̐[�x���
	float shadow_val = tex.Sample(g_sampler, uv).r;
	//return shadow_val;
	//�[�x�e�X�g
	if (depth > shadow_val.r + 0.01f) {
		//��O�ɂ���̂ŃV���h�E�𗎂Ƃ��B
		return 1.0f;
	}
	return 0.0f;
}

float CalcShadow(float3 wp, float zInView)
{
	float shadow = 0.0f;
	//�V���h�E���V�[�o�[������
	if (isShadowReciever == 1)
	{
		//shadow = 1.0f;
		//�e�𗎂Ƃ��B
		//�g�p����V���h�E�}�b�v�̔ԍ����擾�B
		int cascadeIndex = GetCascadeIndex(zInView);
		//���C�g���W���ɕϊ�
		float4 posInLVP = mul(mLVP[cascadeIndex], float4(wp, 1.0f));
		//���C�g���W�n�ł̐[�x�l���v�Z�B
		posInLVP.xyz /= posInLVP.w;

		//�[�x�l���擾
		float depth = posInLVP.z;
		
		//uv���W�ɕϊ�.
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);

		//�ǂ̃V���h�E�}�b�v��
		if (cascadeIndex == 0) {
			//�e�𗎂Ƃ����ǂ����̔���B
			shadow = CalcShadowPercent(g_shadowMap0, shadowMapUV, depth);
		}
		else if (cascadeIndex == 1) {
			//�e�𗎂Ƃ����ǂ����̔���B
			shadow = CalcShadowPercent(g_shadowMap1, shadowMapUV, depth);
		}
		else if (cascadeIndex == 2) {
			shadow = CalcShadowPercent(g_shadowMap2, shadowMapUV, depth);
		}
	}

	return shadow;
}

/*!
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	
	//���[���h���W�v�Z
	float4 pos = mul(mWorld, In.Position);
	//���[���h���W�n
	psInput.worldPos = pos;
	//�J�������W�n�v�Z
	pos = mul(mView, pos);
	//�J�������W�n
	psInput.posInview = pos;
	//�X�N���[�����W�n�v�Z
	pos = mul(mProj, pos);
	
	//�s�N�Z���V�F�[�_�[�Ƀv���W�F�N�V�������W��n��
	psInput.Position = pos;

	//�V���h�E���V�[�o�[�i�e���󂯎��I�u�W�F�N�g�j���ǂ����̔���
	if (isShadowReciever == 1) {
		//�V���h�E���V�[�o�[������
		//�r���[�s��ɕϊ�
		psInput.posInLVP = mul(mLightView, float4 (psInput.worldPos, 1.0f));
		//�v���W�F�N�V�����s��ɕϊ�
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	//�s�N�Z���V�F�[�_�[�ɓn��
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	//�X�L�j���O�����A���[���h���W�B
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
	}
	//�X�L�j���O���ꂽ�A���[���h���W�B
	psInput.SkiningPos = pos;

	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	//�X�N���[�����W�n�ɕϊ�
	pos = mul(mView, pos);
	psInput.posInview = pos;
	pos = mul(mProj, pos);
	//�X�N���[�����W
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(g_sampler, In.TexCoord);
	
	//���C�g�̉e���x
	float3 lig = 0.0f;

	//�f�C���N�V�������C�g�̌v�Z
	for (int i = 0; i < NUM_DIRECTION_LIG; i++)
	{
		if (active == true) {
			//�f�B���N�V�������C�g���L��
			lig += max(0.0f, dot(In.Normal * -1.0f, Direction[i])) * Color[i];
		}
		else if(active == false){
			//�f�B���N�V�������C�g������
			return albedoColor;
		}
	}

	//���ʔ��˂̌v�Z
	for (int i = 0; i < NUM_DIRECTION_LIG; i++)
	{
		if (specPow/*[i]*/ >= 1.0f) 
		{
			//���ʔ��˔��˂�����
			{
				//���C�g�𓖂Ă�ʂ��王�_�ɐL�т�x�N�g���v�Z
				float3 toEyeDir = normalize(eyePos - In.worldPos);
				//���˃x�N�g��
				float3 reflectV = -toEyeDir + 2 * dot(In.Normal, toEyeDir)* In.Normal;
				//���˃x�N�g���ƃf�B���N�V�������C�g�̓��ς���X�y�L�����̋����v�Z
				float3 t = max(0.0f, dot(-Direction[i], reflectV));

				if (Color[i].x != 0 && Color[i].y != 0 && Color[i].z != 0) {
					//�J���[������Ȃ�
					//�X�y�L�����v�Z  pow(x,y) = x��y��
					float3 spec = pow(t, specPow/*[i]*/) * Color[i].xyz;
					//lig�ɉ��Z
					lig += spec;
				}
			}
		}
	}

	//calcShadow�������return 1.0f���A���Ă�����V���h�E��������B
	float f = 0.0f;
	//�V���h�E�𗎂Ƃ��v�Z�B
	f = CalcShadow(In.worldPos, In.posInview.z);
	if (f == 1.0f)
	{
		//�e�������Ă���̂Ń��C�g�̖��������߂�B
		lig *= 0.5f;
	}
	//lig *= f;

	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	//finalColor.x = f;
	return finalColor;
}
//--------------------------------------------------------------------------------------
// �V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�̃G���g���֐�
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4( 0.5f, 0.5f, 0.5f, 1.0f);
}

/*
	�X�L���Ȃ��V���h�E�}�b�v�����p�̒��_�V�F�[�_�[
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
	�X�L������V���h�E�}�b�v�����p�̒��_�V�F�[�_�[
*/
PSInput_ShadowMap VSMain_ShadowMapSkin(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.Position);
	}

	//pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/*
	�s�N�Z���V�F�[�_�[�̃G���g���֐�
*/
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ�
	float z = In.Position.z / In.Position.w;
    return z;
}

