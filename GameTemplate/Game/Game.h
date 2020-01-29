#pragma once
#include "graphics/2D/Sprite.h"
class Game : public IGameObject
{
public:
	Game();
	~Game();

private:
	bool Start()override;
	void Update()override;
	void Draw()override;
	Sprite m_test;
};