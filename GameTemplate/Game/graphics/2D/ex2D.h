/// <summary>
/// 2D�T���v���R�[�h�N���X
/// </summary>
/// <remarks>
/// SpriteRender�쐬�ɂ�tkEngine��
/// �قƂ�Ǔ����X�v���C�g�̍쐬���@�ɂȂ�܂����B
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
		SpriteRender* spriteRender;
	};
}

