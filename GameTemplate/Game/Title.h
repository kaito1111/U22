#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();

private:
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	void Update()override;
	//SpriteRender* m_Sprite = nullptr;
	SpriteRender* m_SSprite = nullptr;
	SpriteRender* m_NSprite = nullptr;
	SpriteRender* m_LoadUp = nullptr;
	SpriteRender* m_LoadDown = nullptr;
	CVector3 m_SPos = { 720.0f,-360.0f,0.0f };
	CVector3 m_NPos = { -720.0f,360.0f,0.0f };
	CQuaternion m_Rot = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_DiffLengh = 0.0f;
};