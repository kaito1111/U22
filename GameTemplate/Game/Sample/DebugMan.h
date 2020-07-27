/// <summary>
/// Player��prefab
/// 1.��{�I�Ȉړ�����(�ړ��A����)
/// 2.�L�����R���ɂ�铖���蔻��
/// 3.�J�X�P�[�h�V���h�E�}�b�v�ɂ��V���h�E����
/// </summary>

#pragma once

class ShadowMap;
#include "character/CharacterController.h"

namespace myEngine {
	class DebugMan : public IGameObject
	{
	public:
		//�R���X�g���N�^
		DebugMan();
		//�f�X�g���N�^
		~DebugMan();
		//�X�^�[�g
		bool Start();
		/// <summary>
		/// �A�j���[�V�����̏�����
		/// </summary>
		void AnimInit();
		//�X�V
		void Update();
		/// <summary>
		/// �ړ�����
		/// </summary>
		void Move();
		/// <summary>
		/// PreRender
		/// <para>�V���h�E�}�b�v�`��</para>
		/// </summary>
		void PreRender();
		//�`��
		void Draw();
	public:
		/// <summary>
		/// SampleMan�̈ʒu�擾
		/// </summary>
		/// <returns></returns>
		const CVector3& GetPosition()
		{
			return m_pos;
		}
	private:
		CVector3 m_pos = CVector3::Zero();				//�f�o�b�O�}���̈ʒu
		CVector3 m_scale = CVector3::One();				//�f�o�b�O�}���̊g�嗦
		CQuaternion m_rot = CQuaternion::Identity();	//�f�o�b�O�}���̉�]��
		SkinModel m_skinModel;							//�f�o�b�O�}���̃X�L�����f��
		ShadowMap* m_shadowMap = nullptr;				//�V���h�E�}�b�v
		CharacterController m_charaCon;					//�L�����R��
		const float m_moveSpeed = -2.5f;				//��b�ړ����x
		//�A�j���[�V�����n �}�W�b�N�i���o�[�_�����
		enum EnAnimationClip {
			enAnimClip_idle,	//�Ђ܂�Ȃ��A�j���[�V����
			enAnimClip_walk,	//�����̂��邢�킟�A�j���[�V����
			enAnimClip_run,		//����������A�j���[�V����
			enAnimClip_Num		//�A�j���[�V�����̐�
		};
		Animation m_animation;							//�A�j���[�V����
		AnimationClip m_animClip[enAnimClip_Num];		//�A�j���[�V�����N���b�v

	};
}
