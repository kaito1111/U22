#pragma once

#include "ShadowMap.h"

namespace myEngine {
	/// <summary>
	/// �I�I�f�o�b�O�}���I�I
	/// �\���@�F�V���h�E�}�b�v�̍쐬���ł���B
	/// �\���A�F�e���o����B
	/// </summary>
	/// <remarks>
	/// �G���W���̋@�\�ǉ��̍ۂȂǊ�����Player�Ƃ��g���̂́A
	/// �C��������̂ō쐬�B
	/// ���f������X�����āA�A�j���[�V�������t�������B
	/// </remarks>
	class DebugMan : public IGameObject
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		DebugMan();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~DebugMan();
		/// <summary>
		/// �X�^�[�g
		/// </summary>
		bool Start() { return true; };
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// Draw��葁���`��
		/// </summary>
		void Render();
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	private:
		CVector3 m_pos = CVector3::Zero();				//�f�o�b�O�}���̈ʒu
		CVector3 m_scale = CVector3::One();				//�f�o�b�O�}���̊g�嗦
		CQuaternion m_rot = CQuaternion::Identity();	//�f�o�b�O�}���̉�]��
		CVector3 m_lightCameraPosition;					//���C�g�J�����̎��_�ʒu
		CVector3 m_lightCameraTarget;					//���C�g�J�����̒����_�ʒu
		SkinModel m_skinModel;							//�f�o�b�O�}���̃X�L�����f��
		ShadowMap* m_shadowMap = nullptr;				//�V���h�E�}�b�v
	};
}
