#pragma once
class PlayerPad;
class NetworkPad;
class IPad;

class TwoP_Pad: public IGameObject
{
	//using NetworkPad = PlayerPad;
public:
	TwoP_Pad();
	~TwoP_Pad();

	void Update() override;

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
	IPad* GetPPad()
	{
		return m_playerPad;
	}
	/// <summary>
	/// ネットワークパッドの取得
	/// </summary>
	/// <returns></returns>
	IPad* GetNPad()
	{
		return m_networkPad;
	}
	/// <summary>
	/// 自分のプレイヤー番号
	/// <para>PlayerPad側になる方の番号を取得</para>
	/// </summary>
	/// <returns></returns>
	int& getPlayerNum()
	{
		return m_PlayerPadNum;
	}

private:
	enum KeyState
	{
		Jump,
		MagN,
		MagS,
		NoMag,
		ShotN,
		ShotS,
		Start
	};
	void PostRender();
	Sprite m_copyMainRtToFrameBufferSprite;	//メインRTVに描かれた絵をフレームバッファにコピーするためのスプライト

	//Player* player[2] = {};
	bool UpdateStop = true;			//Updateを止めるフラグfalseでUpdateする。
	int m_PlayerPadNum = 0;			//playerPadになるpadの番号

	//bool Start()override;
	bool NewGOPlayer = false;		//プレイヤーをNewGOするかどうか

	IPad* m_playerPad;		//プレイヤーのパッド
	IPad* m_networkPad;		//ネットワークのパッド
};

/// <summary>
/// TwoP_Padのインスタンス取得
/// </summary>
/// <returns></returns>
static inline TwoP_Pad& twoP_Pad()
{
	return TwoP_Pad::GetInstance();
}
