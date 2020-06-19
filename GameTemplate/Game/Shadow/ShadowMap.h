/// <summary>
/// �V���h�E�}�b�v
/// </summary>
/// <remarks>
/// �T���v���R�[�h��DebugMan�N���X��Stage�N���X�̃R���X�g���N�^���m�F
/// </remarks>


#pragma once

#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"
#include "SamplerState.h"

namespace myEngine {
	class ShadowMap 
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		ShadowMap();

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~ShadowMap();

		/// <summary>
		/// ������
		/// </summary>
		void Init();

		/// <summary>
		/// �폜
		/// </summary>
		void Release();

		/// <summary>
		/// ���C�g�r���[�s����擾�B
		/// </summary>
		/// <returns></returns>
		CMatrix GetLightViewMatirx() const
		{
			return m_lightViewMatrix;
		}

		/// <summary>
		/// ���C�g�v���W�F�N�V�����s����擾
		/// </summary>
		/// <returns></returns>
		CMatrix GetLightProjMatirx() const
		{
			return m_lightProjMatirx;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// <para>�X�V(���C�g�J�����̒����_���w�肷��o�[�W�����B)</para>
		/// </summary>
		/// <remarks>
		/// ���C�g�r���[�s���A���C�g�v���W�F�N�V�����s����X�V�B
		/// ���t���[���Ăяo�����ƁB
		/// </remarks>
		/// <param name="lightCameraPos">���C�g�J�����̎��_�̍��W</param>
		/// <param name="lightCameraTarget">���C�g�J�����̒����_�̍��W</param>
		void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);

		/// <summary>
		/// ���C�g�̍��W�v�Z
		/// <para></para>
		/// </summary>
		/// <remarks>
		/// ������̒��S���W���Ɍv�Z���Ă����K�v������܂��B
		/// �V���h�E�}�b�v�̉񐔕��񂷂��ƁB
		/// �R�[�h�̏ڍׂ̓J�X�P�[�h�V���h�E������CalcLightPosition.png�Q�ƁB
		/// </remarks>
		/// <param name="lightHeight">���C�g�̍���</param>
		/// <param name="viewFrustomCenterPosition">������̒��S���W</param>
		/// <returns>���C�g�̍��W</returns>
		CVector3 CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition);
		
		/// /// <summary>
		/// ���C�g
		/// </summary>
		void UpdateFromLightTarget();

		/// <summary>
		/// �X�V�i���C�g�J�����̌������w�肷��o�[�W�����B
		/// </summary>
		/// <remarks>
		/// ���C�g�r���[�s��A���C�g�v���W�F�N�V�����s����X�V�B
		/// UpdateFromLightTarget��UpdateFromLightDirection�ǂ��炩��
		/// ���t���[���Ăяo�����ƁB
		/// </remarks>
		/// <param name="lightCameraPos">���C�g�J�����̎��_�̍��W</param>
		/// <param name="lightDir">���C�g�J�����̒����_�̍��W</param>
		void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);

		/// <summary>
		/// <para>�V���h�E�}�b�v�ɃV���h�E�L���X�^�[�������_�����O�B</para>
		/// <para>���̊֐����Ăяo���ƁA�V���h�E�L���X�^�[�̃��X�g�̓N���A����܂��B</para>
		/// <para>���t���[���Ăяo�����ƁB</para>
		/// <para>�������d�v����</para>
		/// <para>���̊֐����Ăяo���O��BginRender,�Ăяo������EndRender���ĂԂ���</para>
		/// <para>�������d�v����</para>
		/// </summary>
		/// <remarks>
		/// �V���h�E�}�b�v�ɕ`�悳���V���h�E�L���X�^�[��
		/// RegistShadowCaster�֐����g�p���ēo�^���ꂽ�L���X�^�[�݂̂ł��B
		/// </remarks>
		void RenderToShadowMap();

		/// <summary>
		/// �V���h�E�L���X�^�[(�e�𐶐�����I�u�W�F�N�g�j�̓o�^
		/// <para>��ɉe�𐶐�����ꍇ���t���[���Ăяo�����ƁB</para>
		/// </summary>
		/// <remarks>
		/// ���̊֐����g���āA�o�^���ꂽ�L���X�^�[��
		/// �V���h�E�}�b�v�ɕ`�悳��܂��B
		/// �o�^���ꂽ�L���X�^�[�̃��X�g��RenderToShadowMap���Ăяo������
		/// �N���A����܂��B
		/// </remarks>
		/// <param name="shadowCaster"></param>
		void RegistShdowCaster(SkinModel* shadowCaster)
		{
			m_shadowCasters.push_back(shadowCaster);
		}

		/// <summary>
		/// �`��ݒ�̃o�b�N�A�b�v
		/// </summary>
		/// <remarks>
		/// 1.�����_�[�^�[�Q�b�g�r���[���o�b�N�A�b�v�B
		/// 2.�[�x�X�e���V���r���[���o�b�N�A�b�v�B
		/// 3.�r���[�|�[�g���o�b�N�A�b�v�B
		/// </remarks>
		void BiginRender();

		/// <summary>
		/// ���̕`��ݒ�ɖ߂�
		/// </summary>
		void EndRender();


		/// <summary>
		/// �V���h�E�}�b�v��SRV���擾
		/// </summary>
		/// <returns></returns>
		ID3D11ShaderResourceView* GetShadowMapSRV()
		{
			return m_shadowMapRT.GetRenderTargetSRV();
		}

	private:
		//�J�X�P�[�h�V���h�E�����p�ϐ�//
		
		/// <summary>
		/// �����̒��g����������ShadowCb���ύX���邱��
		/// </summary>
		struct SShadowCb {
			CMatrix mLVP[NUM_SHADOW_MAP];						//���C�g�r���[�v���W�F�N�V�����s��
			CVector4 texOffset[NUM_SHADOW_MAP];					//Pivot�݂����Ȋ����H
			float shadowAreaDepthInViewSpace[NUM_SHADOW_MAP];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u��
		};

		float m_lightHieght = 2000.0f;									//���C�g�̍���
		int shadowMapWidth = 2048;												//�V���h�E�}�b�v�̕�
		int shadowMapHeight = 2048;											//�V���h�E�}�b�v�̍���
		RenderTarget m_KshadowMapRT[NUM_SHADOW_MAP]; 					//�V���h�E�}�b�v���������ރ����_�[�^�[�Q�b�g
		CMatrix m_LVPMatrix[NUM_SHADOW_MAP];							//���C�g�r���[�v���W�F�N�V�����s��
		SShadowCb m_shadowCbEntity;										//����p
		ConstantBuffer m_shadowCb;										//�V���h�E�p�萔�o�b�t�@
		SamplerState m_fetchShadowMapSampler;							//�V���h�E�}�b�v���t�F�b�`����Ƃ��Ɏg�p����T���v��-
		CVector3 m_lightDirection = CVector3::Down();					//���C�g�̕���

		//�����܂ŃJ�X�P�[�h�V���h�E//

		CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_
		CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_
		CMatrix m_lightViewMatrix;							//���C�g�r���[�s��
		CMatrix	m_lightProjMatirx;							//���C�g�v���W�F�N�V�����s��
		RenderTarget m_shadowMapRT;							//�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g
		std::vector<SkinModel*> m_shadowCasters;			//�V���h�E�L���X�^�[�̔z��
		ID3D11RenderTargetView* oldRenderTargetView;		//�o�b�N�A�b�v�p�����_�[�^�[�Q�b�g�r���[
		ID3D11DepthStencilView* oldDepthStencilView;		//�o�b�N�A�b�v�p�[�x�X�e���V���r���[
		D3D11_VIEWPORT oldViewports;						//�o�b�N�A�b�v�p�r���[�|�[�g
		unsigned int viewport = 1;							//�r���[�|�[�g
	};

}


