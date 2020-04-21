#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

private:
	void Update();
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	SpriteRender* m_SSprite = nullptr;
	SpriteRender* m_NSprite = nullptr;
	CVector3 m_SPos = CVector3::Zero();
	CVector3 m_NPos = CVector3::Zero();
	CQuaternion m_Rot = CQuaternion::Identity();
	float m_angle = 0.0f;
	float m_DiffLengh = 0.0f;
};

