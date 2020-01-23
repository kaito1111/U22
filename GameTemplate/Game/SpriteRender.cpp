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
		//3D空間表示
		m_isDraw3D = isDraw3D;
		//DDS作成
		m_texture.CreateFromDDSTextureFromFile(textFilePath);
		//初期化
		m_sprite.Init(m_texture, w, h);
	}
	void SpriteRender::Update()
	{
		//テクスチャの更新
		m_sprite.SetTextrue(m_texture);
		//ワールド座標の更新とピボットの更新
		m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
	}
	void SpriteRender::ForwardRender(RenderContext& rc)
	{
		if (m_isDraw3D == true) {
			m_sprite.Draw(rc, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
		}
	}
	void SpriteRender::PostRender(RenderContext& rc)
	{
		if (m_isDraw3D == false) {
			m_sprite.Draw(rc, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
		}
	}
}

