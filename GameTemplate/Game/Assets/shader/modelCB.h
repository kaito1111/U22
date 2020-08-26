/*
	<Sum>
	���f���p�萔�o�b�t�@
	<Rem>
	�X���b�g�ԍ�������������
	�@��CPU���̃X���b�g�ԍ����ASkinModelShaderConst.h���Q�Ƃ��������ƁB
	�ϐ�������������
	�@��CPU���A�e�萔�o�b�t�@�������Ă���(UpdateSubResources)����Ă���ꏊ���������邱�ƁB
*/

//���C�g�̐�
static const int NUM_DIRECTION_LIG = 4;

//���ӃV���h�E�}�b�v�̖������₵����AshadowCb�̃����o�����蓖�ĂĂ���
//���W�X�^�ԍ����Ē�������K�v������܂��B
static const int NUM_SHADOW_MAP = 3;

/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0) {
	float4x4 mWorld;		//���[���h�s��
	float4x4 mView;			//�r���[�s�N
	float4x4 mProj;			//�v���W�F�N�V�����s��
	//�V���h�E�֘A//
	float4x4 mLightView;	//���C�g�r���[�s��
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O 0->OFF 1->ON
};

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
cbuffer ShadowCb : register(b3) {
	float4x4 mLVP[NUM_SHADOW_MAP];		//���C�g�r���[�v���W�F�N�V�����s��
	float4 shadowAreaDepthInViewSapce;	//�J������Ԃŉe�𗎂Ƃ��G���A x = shadow0 y = shadow1 z= shadow2
}
