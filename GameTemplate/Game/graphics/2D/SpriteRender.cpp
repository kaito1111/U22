/// <summary>
/// SpriteRender
/// </summary>
/// <remarks>
/// Sprite�����_�[�����b�v���Ă邾���̃N���X�ł�
/// �ڍ׏�����Sprite�N���X�����Ă�������
/// </remarks>

#include "stdafx.h"
#include "SpriteRender.h"

namespace myEngine {
	SpriteRender::SpriteRender()
	{
	}
	SpriteRender::~SpriteRender()
	{
	}
	void SpriteRender::Init(const wchar_t* textFilePath, float w, float h, bool isDraw3D)
	{
		//3D��ԕ\��
		m_isDraw3D = isDraw3D;
		//DDS�쐬
		m_texture.CreateFromDDSTextureFromFile(textFilePath);
		//������
		m_sprite.Init(m_texture.GetBody(), w, h);
	}
	void SpriteRender::Update()
	{
		//�e�N�X�`���̍X�V
		m_sprite.SetTextrue(m_texture.GetBody());
		//���[���h���W�̍X�V�ƃs�{�b�g�̍X�V
		m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
	}
	void SpriteRender::ForwardRender()
	{
		if (m_isDraw3D == false) {
			m_sprite.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix(), m_w);
		}
	}
	void SpriteRender::Draw()
	{
		if (m_isDraw3D == false) {
			m_sprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), m_w);
		}
		else {
			m_sprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), m_w);
		}
	}

	void SpriteRender::PostRender()
	{
		if (m_isDraw3D == false) {
			m_sprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), m_w);
		}
		else {
			m_sprite.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix(), m_w);
		}
	}
}

