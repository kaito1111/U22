#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"

class Game : public IGameObject//public Magnet
{
public:
	Game();
	~Game();

private:
	bool Start()override;
	void Update()override;
	void Sample();
	SpriteRender* m_test=nullptr;
	SoundSource	m_se;
	Effect* effect = nullptr;
};