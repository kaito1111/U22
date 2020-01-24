/// <summary>
/// 2Dサンプルコードクラス
/// </summary>
/// <remarks>
/// SpriteRender作成につきtkEngineと
/// ほとんど同じスプライトの作成方法になりました。
/// </remarks>

#pragma once

#include "graphics/2D/Sprite.h"
#include "SpriteRender.h"
#include "GPUView/ShaderResourceView.h"

namespace myEngine{
	class ex2D : public IGameObject
	{
	public:
		ex2D();
		~ex2D();
		void Update();
		void Draw();
		//CVector3 m_position = CVector3::Zero();
		//CQuaternion m_rot = CQuaternion::Identity();
		//CVector3 m_scale = CVector3::One();
		//ShaderResourceView m_tex_dummy;
		//Sprite m_dummy_Sprite;
		SpriteRender* spriteRender;
	};
}

