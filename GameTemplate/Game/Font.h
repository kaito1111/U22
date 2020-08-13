#pragma once

namespace myEngine {
	class CFont
	{
	public:
		CFont();
		~CFont();
		/// <summary>
		/// �t�H���g��ݒ�B
		/// </summary>
		/// <param name="font"></param>
		void SetFont(DirectX::SpriteFont* font)
		{
			m_spriteFont = font;
		}
		/// <summary>
		/// �`��J�n�����B
		/// </summary>
		void Begin();
		/// <summary>
		/// �`��I�������B
		/// </summary>
		void End();
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="text">�\������e�L�X�g</param>
		/// <param name="pos">�ʒu</param>
		/// <param name="color">�F</param>
		/// <param name="rotation">��]</param>
		/// <param name="scale">�傫��</param>
		/// <param name="pivot">��_</param>
		void Draw(
			wchar_t const* text,
			const CVector2& pos,
			const CVector4& color = CVector4::White(),
			float rotation = 0.0f,
			float scale = 1.0f,
			CVector2 pivot = {0.5f, 0.5f}
		);

	private:
		DirectX::SpriteBatch*		m_spriteBatch = nullptr;	//�X�v���C�g�o�b�`�B
		DirectX::SpriteFont*		m_spriteFont = nullptr;		//�X�v���C�g�t�H���g�B
		ID3D11RasterizerState*		m_RasState = nullptr;		//�o�b�N�A�b�v���X�^���C�U�[�B
		ID3D11BlendState*			m_BleState = nullptr;		//�o�b�N�A�b�v�u�����h�X�e�[�g�B
		ID3D11DepthStencilState*	m_DepthState = nullptr;		//�f�v�X�X�e���V���X�e�[�g�B
		CMatrix m_scaleMat;									//�X�v���C�g�̃X�P�[���B
	};
}

