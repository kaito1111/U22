#pragma once
#include "graphics/2D/Sprite.h"
#include "graphics/2D/SpriteRender.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();

private:
	bool Start()override;
	void Update()override;
	SpriteRender* m_test=nullptr;
};