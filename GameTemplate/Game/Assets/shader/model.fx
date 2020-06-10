/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�V���h�E�}�b�v
Texture2D<float4> shadowMap : register(t2);
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler g_sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;		//���[���h�s��
	float4x4 mView;			//�r���[�s�N
	float4x4 mProj;			//�v���W�F�N�V�����s��
	//�V���h�E�֘A//
	float4x4 mLightView;	//���C�g�r���[�s��
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O 0->OFF 1->ON
};

//���C�g�̐�
static const int NUM_DIRECTION_LIG = 4;

/*
	���C�g�p�萔�o�b�t�@ 
*/
cbuffer LightCb : register(b1) {
	float3		Direction[NUM_DIRECTION_LIG];	//�J�����̕���
	float4		Color[NUM_DIRECTION_LIG];		//�J���[
	float3		eyePos;							//���_�̍��W
	bool		active = true;					//�A�N�e�B�u
	float		specPow/*[NUM_DIRECTION_LIG]*/;		//���ʔ��˂̍i�� �Ō�ɏ����āI
};	

/*
	�V���h�E�}�b�v�p�̒萔�o�b�t�@
*/
//cbuffer ShadowMapCb : register(b1) {
//	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��B
//}

//���ӃV���h�E�}�b�v�̖������₵����AshadowCb�̃����o�����蓖�ĂĂ���
//���W�X�^�ԍ����Ē�������K�v������܂��B
#define NUM_SHADOW_MAP 3
/*
	�V���h�E�}�b�v�p�̒萔�o�b�t�@
*/
cbuffer ShadowCb : register(b2) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//���C�g�r���[�v���W�F�N�V�����s��
	float4 texOffset[NUM_SHADOW_MAP];	//�V���h�E�}�b�v�T�C�Y
	float4 shadowAreaDepthInViewSapce;	//�J������Ԃŉe�𗎂Ƃ��G���A
}

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;
};

/*
	�V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�ւ̓��͍\����
*/
struct PSInput_ShadowMap {
	float4 Position			: SV_POSITION;	//���W
};

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
	
	psInput.worldPos = pos;

	pos = mul(mView, pos);
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
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);

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

	//�V���h�E���V�[�o�[�������ꍇ�͉e�̌v�Z
	if (isShadowReciever == 1) {
		
		//���C�g�r���[�v���W�F�N�V������Ԃ��猩������
		//�ł���O�̐[�x�l���V���h�E�}�b�v����擾
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		//LVP�s��ŕϊ������u���W�v�i-1�`1�j��UV���W�i0�`1�j�ɕϊ�
		{
			//-1~1��0~1�ɂ��邽�߂�0.5����Z����0.5�𑫂�
			//�ȈՓI�Ɍ����ƕ��`�������ɕϊ�
			shadowMapUV *= float2(0.5f, -0.5f);
			shadowMapUV += 0.5f;
		}

		//�V���h�E�}�b�v�͈͓̔����̔���
		if (shadowMapUV.x < 1.0f && shadowMapUV.y < 1.0f &&
			shadowMapUV.x > 0.0f && shadowMapUV.y > 0.0f)
		{
			//LVP��Ԃł̐[�x�l�v�Z
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾
			float zInShadowMap = shadowMap.Sample(g_sampler, shadowMapUV);
			//�V���h�E�A�N�l�i�e�̂�����j��h������
			if (zInLVP > zInShadowMap + 0.01f) {
				//�e�������Ă���̂Ō����キ����
				lig *= 0.5f;
			}
		}
	}

	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
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
	�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[
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
	�s�N�Z���V�F�[�_�[�̃G���g���֐�
*/
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ�
	return In.Position.z / In.Position.w;
}

