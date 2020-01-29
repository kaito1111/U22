/// <summary>
/// �X�v���C�g
/// </summary>

#include "graphics/Primitive.h"

#pragma once

namespace myEngine {
	class Sprite
	{
	public:
		static const CVector2	DEFAULT_PIVOT;		//�s�{�b�g
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Sprite();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Sprite();
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="tex">�e�N�X�`��</param>
		/// <param name="w">��</param>
		/// <param name="h">����</param>
		void Init(ID3D11ShaderResourceView* tex, float w, float h);
		/// <summary>
		/// �e�N�X�`���̐ݒ�
		/// </summary>
		/// <param name="tex">�e�N�X�`��</param>
		void SetTextrue(ID3D11ShaderResourceView& tex)
		{
			m_textureSRV = &tex;
		}
		/// <summary>
		/// �ʒu�̐ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ��Z�J���[��ݒ�
		/// </summary>
		/// <param name="mulColor">��Z�J���[</param>
		void SetMulColor(const CVector4& mulColor)
		{
			m_mulColor = mulColor;
		}
		/// <summary>
		/// �X�V����
		/// </summary>
		/// <param name="trans">���s�ړ�</param>
		/// <param name="rot">��]</param>
		/// <param name="scale">�g��</param>
		/// <param name="pivot">��_</param>
		/// <remarks>
		/// pivot�̋���
		/// (0.5,0.5)���S	(0.0,0.0)����	(1.0,1.0)�E��
		/// Unity��uGUI�ƈꏏ
		/// </remarks>
		void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		/// <param name="viewMatrix">�J�����̈ʒu</param>
		/// <param name="projMatrix">��p�Ƃ�</param>
		void Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix);

	private:
		//�\���̌^�X�v���C�g�p�̒萔�o�b�t�@
		struct SSpriteCB {
			CMatrix WVP;			//���[���h�r���[�v���W�F�N�V�����s��
			CVector4 m_mulColor;	//��Z�J���[
			int kj;
		};
		CVector3					m_position = CVector3::Zero();			//���W
		CQuaternion					m_rotation = CQuaternion::Identity();	//��]
		CVector3					m_scale = CVector3::Zero();				//�X�P�[��
		CMatrix						m_world = CMatrix::Identity();			//���[���h�s��
		Primitive					m_primitive;							//�v���~�e�B�u
		Shader						m_ps;									//�s�N�Z���V�F�[�_�[
		Shader						m_vs;									//���_�V�F�[�_�[
		ConstantBuffer				m_cb;									//�萔�o�b�t�@
		CVector4					m_mulColor = CVector4::White();			//��Z�J���[
		ID3D11ShaderResourceView*	m_textureSRV = nullptr;					//�e�N�X�`��
		ID3D11SamplerState*			SamplerState;							//�T���v���X�e�[�g
		ID3D11BlendState*			BlendState;								//�u�����h�X�e�[�g
		bool				m_isInited = false;						//�������t���O
		CVector2			m_size = CVector2::Zero();				//�T�C�Y(�傫��)
	};
}



