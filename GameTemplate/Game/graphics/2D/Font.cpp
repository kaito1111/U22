#include "stdafx.h"
#include "Font.h"

namespace myEngine {
	CFont::CFont()
	{
		//���������`
		m_spriteBatch = graphicsEngine().GetSpriteBatch();
		m_spriteFont = graphicsEngine().GetSpriteFont();
		GraphicsEngine& ge = GraphicsEngine();
		//�g��x�B�Ƃ肠�����A111�ŌŒ�
		m_scaleMat.MakeScaling(
			{1.0f, 1.0f, 1.0f}
		);
	}

	CFont::~CFont()
	{
	}

	void CFont::Begin()
	{
		//���݂̃����_�[�X�e�[�g��ۑ�
		graphicsEngine().PushRenderState();
		//�`��ݒ�B
		m_spriteBatch->Begin(
			DirectX::SpriteSortMode_Deferred,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			m_scaleMat
		);
	}

	void CFont::End()
	{
		//�`��I���B
		m_spriteBatch->End();
		//�����_�[�X�e�[�g�����Ƃɖ߂��B
		graphicsEngine().SetRenderState();
	}

	void CFont::Draw(
		wchar_t const* text,
		const CVector2& pos,
		const CVector4& color,
		float rotation,
		float scale,
		CVector2 pivot
	)
	{
		if (text == nullptr) {
			//�Ȃɂ��Ȃ�����A�Ȃɂ�����I
			return;
		}
		//UV���W�̉����GameProg�Q�ƁB
		//Unity��pivot�ɍ��킹��
		pivot.y = 1.0f - pivot.y;
		DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
		//���W�v�Z
		CVector2 position = pos;
		position.x += FRAME_BUFFER_W;
		position.y = -position.y + FRAME_BUFFER_H;
		//�`��
		m_spriteFont->DrawString(
			m_spriteBatch,
			text,
			position.vec,
			color,
			rotation,
			DirectX::XMFLOAT2(pivot.x, pivot.y),
			scale
		);
	}
}