#pragma once
class Game : public IGameObject
{
public:
	Game();
	~Game();

private:
	bool Start()override;
	void Update()override;
};