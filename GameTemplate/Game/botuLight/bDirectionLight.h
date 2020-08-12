/// <summary>
/// �f�B���N�V�������C�g
/// </summary>
/// <remarks>�J�����̃J���[�A�����A���f�[�^��Ԃ����x�̃N���X</remarks>

#pragma once

#include "blight.h"
#include "LightBase.h"

namespace myEngine {
	class DirectionLight : public LightBase
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		DirectionLight();
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~DirectionLight();
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool StartSub();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override final;
		/// <summary>
		/// ���C�g�̕����ݒ�
		/// </summary>
		/// <param name="direction">���C�g�̕���</param>
		void SetDirection(const CVector3& direction);
		/// <summary>
		/// �J�����̌������擾
		/// </summary>
		/// <returns>�J�����̌���</returns>
		const CVector3& GetDirection() const
		{
			return m_lig.direction;
		}
		/// <summary>
		/// �J�����̃J���[��ݒ�
		/// </summary>
		/// <param name="color">�J�����̃J���[</param>
		void SetColor(const CVector4& color);
		/// <summary>
		/// �f�B���N�V�������C�g�̐��f�[�^
		/// </summary>
		/// <returns>���f�[�^</returns>
		SDirectionLight& GetRawData()
		{
			return m_lig;
		}

	private:
		SDirectionLight		m_lig;			//�f�B���N�V�������C�g
	};
}
