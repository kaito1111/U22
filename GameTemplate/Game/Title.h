#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	void Update()override;
	SpriteRender* m_Sprite = nullptr;
};