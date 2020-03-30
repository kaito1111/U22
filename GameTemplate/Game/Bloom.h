#pragma once

namespace myEngine {
	class PostEffect;
	/// <summary>
	/// �u���[��
	/// </summary>
	class Bloom 
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Bloom();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Bloom();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// �`��
		/// </summary>
		void Draw(PostEffect& postEffect);
	private:
		/// <summary>
		/// �����_�[�^�[�Q�b�g�̏�����
		/// </summary>
		void InitRenderTarget();
		/// <summary>
		/// �V�F�[�_�[�̏�����
		/// </summary>
		void InitShader();
		/// <summary>
		/// �A���t�@�u�����h�X�e�[�g�̏�����
		/// </summary>
		void InitAlphaBlendState();
		/// <summary>
		/// �萔�o�b�t�@�̏�����
		/// </summary>
		void InitConstantBuffer();
		/// <summary>
		/// �T���v���[�X�e�[�g�̏�����
		/// </summary>
		void InitSamplerState();
	private:
		static const int NUM_WEIGHTS = 8;	//�d�݂̐�
		/// <summary>
		/// �u���[�p�̃p�����[�^�o�b�t�@
		/// <para>�����ύX������AShader/bloom.fx��CBBlur�̒��g���ύX����悤��</para>
		/// </summary>
		struct SBlurParam {
			CVector4 offset;			//�Ԋu
			float weights[NUM_WEIGHTS];	//�d��
		};
		ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���[�X�e�[�g
		ID3D11BlendState* m_disableBlendState = nullptr;	//���𖳌��ɂ���u�����h�X�e�[�g
		ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�u�����h�X�e�[�g
	private:
		RenderTarget m_luminaceRT;		//�P�x���o�p�̃����_�����O�^�[�Q�b�g
		RenderTarget m_downSamplingRT[2];	//�u���[�������邽�߂̃_�E���T���v�����O
		Shader m_vs;					//���̂܂܂̒��_�V�F�[�_�[
		Shader m_psLuminance;			//�P�x���o�p�̃s�N�Z���V�F�[�_�[
		Shader m_vsXBlur;				//X�u���[�p���_�V�F�[�_�[
		Shader m_vsYBlur;				//Y�u���[�p���_�V�F�[�_�[
		Shader m_psBlur;				//�u���[�p�s�N�Z���V�F�[�_�[
		Shader m_psFinal;				//�ŏI�����p�̃s�N�Z���V�F�[�_�[
		ID3D11Buffer* m_blurParamCB = nullptr;	//�u���[�p�����[�^�[�p�̒萔�o�b�t�@

	};
}
