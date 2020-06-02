#pragma once

#include "Bloom/Bloom.h"

namespace myEngine {
	/// <summary>
	/// �|�X�g�G�t�F�N�g
	/// </summary>
	class PostEffect 
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		PostEffect();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~PostEffect();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
		/// <summary>
		/// �t���X�N���[���`��
		/// <para>�ݒ肵����VS,PS��������</para>
		/// </summary>
		/// <param name="vs">���_�V�F�[�_�[</param>
		/// <param name="ps">�s�N�Z���V�F�[�_�[</param>
		void DrawFullScreenQuadPrimitive(Shader& vsShader, Shader& psShader);
	private:
		/// <summary>
		/// �t���X�N���[���`��p�l�p�`�v���~�e�B�u
		/// </summary>
		void InitFullScreenQuadPrimitive();
	private:
		Bloom  m_bloom;								//�u���[��
		ID3D11Buffer* m_vertexBuffer = nullptr;		//���_�o�b�t�@
		ID3D11InputLayout* m_inputLayout = nullptr;	//���̓��C�A�E�g
	};

}

