#pragma once
#include "Sprite.h"

namespace myEngine {
	class SpriteRender : public IGameObject
	{
	public:
		SpriteRender();
		~SpriteRender();
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="texFilePath">�e�N�X�`���̃t�@�C���p�X</param>
		/// <param name="w">��</param>
		/// <param name="h">����</param>
		void Init(const wchar_t* texFilePath, float w, float h, bool isDraw3D);
		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W�̎擾
		/// </summary>
		/// <returns>���W</returns>
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rot">��]</param>
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns>��]</returns>
		const CQuaternion& GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="scale">�X�P�[��</param>
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �g�嗦�̎擾
		/// </summary>
		/// <returns>�X�P�[��</returns>
		const CVector3& GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// �s�{�b�g�̐ݒ�
		/// </summary>
		/// <param name="pivot">�s�{�b�g</param>
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
		void SetMulColor(const CVector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
	public:
		void Update() override final;
		void ForwardRender(RenderContext& rc);
		void PostRender(RenderContext& rc);
	private:
		bool m_isDraw3D = false;					//3D��ԕ`��H
		//ID3D11ShaderResourceView m_texture;				//�e�N�X�`��
		Sprite m_sprite;							//�X�v���C�g
		CVector3 m_position= CVector3::Zero();						//�|�W�V����
		CQuaternion m_rotation = CQuaternion::Identity();						//��]
		CVector3 m_scale = CVector3::Zero();		//�g�嗦
		CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g
	};
}


