#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	float GetLengh() {
		return m_DiffLengh;
	}
private:
	void Update();
	SpriteRender* m_SSprite = nullptr;
	SpriteRender* m_NSprite = nullptr;
	SpriteRender* m_LoadUp = nullptr;
	SpriteRender* m_LoadDown = nullptr;
	CVector3 m_SPos = { 720.0f,-360.0f,0.0f };
	CVector3 m_NPos = { -720.0f,360.0f,0.0f };
	CQuaternion m_Rot = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_DiffLengh = 5000000.0f;
};

