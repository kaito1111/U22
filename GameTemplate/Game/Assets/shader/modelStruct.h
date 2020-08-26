/*
	���f���֘A�̍\���́B
	������ς�����Amodel.fx�̏������ς��邱�ƁB
*/

/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;			//���_���W�B
	float3 Normal : NORMAL;					//�@���B
	float3 Tangent : TANGENT;				//�ڃx�N�g���B
	float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
	float4 Position : SV_Position;			//���_���W�B
	float3 Normal : NORMAL;					//�@���B
	float2 TexCoord : TEXCOORD0;			//UV���W�B
	float3 Tangent : TANGENT;				//�ڃx�N�g���B
	uint4  Indices : BLENDINDICES0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
	float4 Weights : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput {
	float4 Position : SV_Position;		//�s�N�Z�����W
	float3 Normal : NORMAL;				//�@��
	float3 Tangent : TANGENT;			//�ڃx�N�g��
	float2 TexCoord : TEXCOORD0;		//UV���W
	float3 worldPos : TEXCOORD1;		//���[���h���W
	float4 posInLVP : TEXCOORD2;		//���C�g�r���[���W
	float4 SkiningPos : TEXCOORD3;		//�X�L�j���O�����A���[���h���W�B
	float4 posInview : TEXCOORD4;		//�r���[���W
};

/*
	�V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�ւ̓��͍\����
*/
struct PSInput_ShadowMap {
	float4 Position : SV_POSITION;	//���W
};