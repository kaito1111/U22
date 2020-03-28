#pragma once

namespace myEngine {
	/// <summary>
	/// �u���[��
	/// </summary>
	class Bloom : public IGameObject 
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
		/// �T���v���[�X�e�[�g�̏�����
		/// </summary>
		void InitSamplerState();
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	private:
		ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���[�X�e�[�g
		ID3D11BlendState* m_disableBlendState = nullptr;	//���𖳌��ɂ���u�����h�X�e�[�g
		ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�u�����h�X�e�[�g
	private:
		RenderTarget m_luminaceRT;		//�P�x���o�p�̃����_�����O�^�[�Q�b�g
		RenderTarget m_downSamplingRT;	//�u���[�������邽�߂̃_�E���T���v�����O
		Shader m_vs;					//���̂܂܂̒��_�V�F�[�_�[
		Shader m_psLuminance;			//�P�x���o�p�̃s�N�Z���V�F�[�_�[
		Shader m_vsXBlur;				//X�u���[�p���_�V�F�[�_�[
		Shader m_vsYBlur;				//Y�u���[�p���_�V�F�[�_�[
		Shader m_psBlur;				//�u���[�p�s�N�Z���V�F�[�_�[
		Shader m_psFinal;				//�ŏI�����p�̃s�N�Z���V�F�[�_�[


	};
}
