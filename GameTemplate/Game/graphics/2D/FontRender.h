/// <summary>
/// �t�H���g�����_�[�B
/// </summary>
/// <remarks>
/// GameObjectManager���ŊǗ�����A�t�H���g�̃��b�p�[�N���X�B
/// Draw�̃^�C�~���O���A�G���W���̃f�t�H���g�Ăяo���ł����Ȃ炱�����g���B
/// �Ⴄ�ꍇ�́A�W���̃t�H���g�N���X���g�����B
/// </remarks>

#pragma once

namespace myEngine {
	class CFontRender : public IGameObject
	{
	public:
		/// <summary>
		/// �t�H���g�ݒ�B
		/// </summary>
		void SetFont(DirectX::SpriteFont* font)
		{
			m_font.SetFont(font);
		}
		/// <summary>
		/// �e�L�X�g��ݒ�B
		/// <para>�������ł��B</para>
		/// <para>��{Unsafe�Ŏg����Ǝv������A�g���ĂȁB</para>
		/// </summary>
		/// <param name="text">�e�L�X�g�B</param>
		void SetText(const wchar_t* text)
		{
			if (wcscmp(m_text.c_str(), text) != 0) {
				//������ɕύX���������B
				//�����ŃR�s�[����������H
				m_text = text;
			}
		}
		/// <summary>
		/// �A���Z�[�t�ŁASetText�B
		/// <para>�g���O�ɁA�Ƃ肠��������(remarks)�݂ĂˁB</para>
		/// </summary>
		/// <remarks>
		/// �����o�ϐ��ň����ɓn���̒�`������A�܂��o�O��Ȃ��͂��B
		/// ���[�J���ϐ��ň����ɓn���̒�`������A�o�O���B
		/// �Ӗ��킩��Ȃ��ꍇ�́A�ʏ�Ŏg���Ă��������B
		/// �����o�ϐ��ɏ����Ă��������Ȃ�����A�����Ă��������B
		/// </remarks>
		/// <param name="text"></param>
		void SetTextUnsafe(const wchar_t* text)
		{
			//�R�s�[���������Ȃ��B
			m_textUnsafe = text;
		}
		/// <summary>
		/// �t�H���g��\��������W�ݒ�B
		/// <para>��ʒ�����0,0</para>
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const CVector2& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// �t�H���g�̐F��ݒ�B
		/// </summary>
		/// <param name="color">�J���[</param>
		void SetColor(const CVector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// �t�H���g�̐F��ݒ�B
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const CVector4& color)
		{
			m_color = color;
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(float rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// �g�嗦�B
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �s�{�b�g�̐ݒ�B
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
	private:
		void PostRender() override;
	private:
		CFont			m_font;								//�t�H���g�B
		std::wstring	m_text;								//�e�L�X�g�B
		const wchar_t*	m_textUnsafe;						//�A���Z�[�t�e�L�X�g�B
		CVector2		m_position = CVector2::Zero();		//���W�B(0.0f,0.0f)�Ő^�񒆁B
		CVector4		m_color = CVector4::White();		//�J���[�B
		float			m_rotation = 0.0f;					//��]�B
		float			m_scale = 1.0f;						//�X�P�[���B
		CVector2		m_pivot = {0.5f, 0.5f};				//�s�{�b�g�B
	};
}
