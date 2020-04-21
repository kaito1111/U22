#pragma once
class Player;

class TwoP_Pad: public IGameObject
{
public:
	TwoP_Pad();
	~TwoP_Pad();

private:
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	SpriteRender* m_ManualSprite = nullptr;

	//Player* player[2] = {};
	bool UpdateStop = true;			//Updateを止めるフラグfalseでUpdateする。
	//bool Start()override;
	void Update()override;
	bool NewGOPlayer = false;		//プレイヤーをNewGOするかどうか
	float m_Manual_W = 0.0f;
};
