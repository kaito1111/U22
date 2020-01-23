#pragma once

#include "Sprite.h"
#include "RenderContext.h"
#include "GPUView/ShaderResourceView.h"
#include "SpriteRender.h"

namespace myEngine{
	class ex2D : public IGameObject
	{
	public:
		ex2D();
		~ex2D();
		void Update();
		void Draw();
		CVector3 m_position = CVector3::Zero();
		CQuaternion m_rot = CQuaternion::Identity();
		CVector3 m_scale = CVector3::One();
		SpriteRender* m_spriteRender = nullptr;
	};
}

