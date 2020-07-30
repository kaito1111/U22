#pragma once
#include "PlayerPad.h"

class TwoP_Pad: public IGameObject
{
	using NetworkPad = PlayerPad;
public:
	TwoP_Pad();
	~TwoP_Pad();

	//シングルトン
	static TwoP_Pad& GetInstance()
	{
		static TwoP_Pad Instance;
		return Instance;
	}

	/// <summary>
	/// プレイヤーパッドの取得
	/// </summary>
	/// <returns></returns>
	PlayerPad* GetPPad()
	{
		return m_playerPad;
	}
	/// <summary>
	/// ネットワークパッドの取得
	/// </summary>
	/// <returns></returns>
	const NetworkPad* GetNPad()
	{
		return m_networkPad;
	}

private:
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト
	SpriteRender* m_ManualSprite = nullptr;

	//Player* player[2] = {};
	bool UpdateStop = true;			//Updateを止めるフラグfalseでUpdateする。
	int m_PlayerPadNum = 0;

	//bool Start()override;
	void Update()override;
	bool NewGOPlayer = false;		//プレイヤーをNewGOするかどうか
	float m_Manual_W = 0.0f;
	SpriteRender* m_ButtonSprite = nullptr;

	PlayerPad* m_playerPad = nullptr;			//プレイヤーのパッド
	NetworkPad* m_networkPad = nullptr;		//ネットワークのパッド
};

/// <summary>
/// TwoP_Padのインスタンス取得
/// </summary>
/// <returns></returns>
static inline TwoP_Pad& twoP_Pad()
{
	return TwoP_Pad::GetInstance();
}
