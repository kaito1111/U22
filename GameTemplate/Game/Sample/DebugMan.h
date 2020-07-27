/// <summary>
/// Player��prefab
/// 1.��{�I�Ȉړ�����
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
		void PreRender();
		/// <summary>
		/// �`��
		/// </summary>
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
		CVector3 m_moveSpeed = CVector3::Zero();		//�ړ����x
	};
}
