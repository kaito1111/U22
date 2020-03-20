/// <summary>
/// �V���h�E�}�b�v
/// </summary>

#pragma once

#include "graphics/RenderTarget.h"
#include "graphics/SkinModel.h"

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
		/// ���t���[���Ăяo�����ƁB
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
		/// �V���h�E�}�b�v��SRV���擾
		/// </summary>
		/// <returns></returns>
		ID3D11ShaderResourceView* GetShadowMapSRV()
		{
			return m_shadowMapRT.GetRenderTargetSRV();
		}

	private:
		CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_
		CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_
		CMatrix m_lightViewMatrix;							//���C�g�r���[�s��
		CMatrix	m_lightProjMatirx;							//���C�g�v���W�F�N�V�����s��
		RenderTarget m_shadowMapRT;							//�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g
		std::vector<SkinModel*> m_shadowCasters;			//�V���h�E�L���X�^�[�̔z��
	};

}


