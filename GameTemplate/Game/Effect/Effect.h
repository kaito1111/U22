/// <summary>
/// �G�t�F�N�g
/// �`��̓G�t�F�N�g�G���W�����܂Ƃ܂čs���B	
/// </summary>

#pragma once
#include "GameObject/IGameObject.h"

namespace myEngine {
	class Effect : public IGameObject
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Effect();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Effect();
		/// <summary>
		/// �����I�ȉ��
		/// </summary>
		void Release();
		/// <summary>
		/// �G�t�F�N�g�̍Đ�
		/// <para>float x y z �������œn�����ق������������H</para>
		/// </summary>
		/// <param name="filePath">�Đ�����G�t�F�N�g�̃p�X</param>
		void Play(const wchar_t* filePath);
		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ��]�̐ݒ�
		/// </summary>
		/// <param name="rot">��]</param>
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="scale">�g�嗦</param>
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �G�t�F�N�g���Đ������̔���
		/// </summary>
		/// <returns>�Đ���/��~��</returns>
		bool IsPlay() const
		{
			return EffectEngineObj().GetEffekseerManager()->GetShown(m_handle);
		}
		/// <summary>
		/// �X�V
		/// </summary>
		void Update(); //override;
	private:
		Effekseer::Effect*				m_effect = nullptr;			//�G�t�F�N�g
		Effekseer::Handle				m_handle = -1;				//�n���h��
		CVector3 m_position =			CVector3::Zero();			//���W
		CQuaternion m_rotation =		CQuaternion::Identity();	//��]
		CVector3 m_scale =				CVector3::One();			//�g�嗦
	};
}

