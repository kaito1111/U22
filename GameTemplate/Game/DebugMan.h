/// <summary>
/// �I�I�f�o�b�O�}���I�I
/// </summary>

#pragma once

#include "ShadowMap.h"

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
		/// �`��
		/// </summary>
		void Render();
	private:
		CVector3 m_pos = CVector3::Zero();
		CVector3 m_scale = CVector3::One();
		CQuaternion m_rot = CQuaternion::Identity();
		SkinModel m_skinModel;
	};
}
