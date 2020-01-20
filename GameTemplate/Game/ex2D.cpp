#include "stdafx.h"
#include "GameCamera.h"
#include "ex2D.h"

namespace myEngine {
	ex2D::ex2D()
	{
		//DDSの作成
		m_tex_dummy.CreateFromDDSTextureFromFile(L"Assets/sprite/utc_all2.dds");
		//スプライトの初期化
		m_dummy_Sprite.Init(m_tex_dummy.GetBody(), 200.0f, 200.0f);

	}


	ex2D::~ex2D()
	{
	}

	void ex2D::Update()
	{
		//m_position.x++;
		//ワールド座標の更新
  		m_dummy_Sprite.Update(m_position, m_rot, m_scale);
	}

	void ex2D::Draw()
	{
		//描画
		m_dummy_Sprite.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}
