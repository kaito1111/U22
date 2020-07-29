/// <summary>
/// Playerパッド
/// </summary>

#pragma once
#include "IPad.h"

class PlayerPad : public IPad
{
public:
	//コンストラクタ
	PlayerPad();
	/// <summary>
	/// パッドの初期化
	/// </summary>
	/// <param name="PadNum"></param>
	/// <returns></returns>
	void Init(int PadNum);
	/// <summary>
	/// 更新
	/// <para>GameObjectManager下で管理されているので呼び出さないでください。</para>
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// X軸方向の移動
	/// </summary>
	/// <returns></returns>
	virtual float& MoveX() override
	{
		float X = g_Pad[m_PadNum].GetLStickXF();
		return X;
	}
	/// <summary>
	/// Z軸方向の移動
	/// </summary>
	/// <returns></returns>
	virtual float& MoveZ() override
	{
		float Z = g_Pad[m_PadNum].GetLStickYF();
		return Z;
	}
	/// <summary>
	/// ジャンプ判定
	/// </summary>
	/// <returns></returns>
	virtual bool IsJump() override;
	/// <summary>
	/// N極に切り替え判定
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagN() override;
	/// <summary>
	/// S極に切り替え判定
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagS() override;
	/// <summary>
	/// 磁力なくす判定
	/// </summary>
	/// <returns></returns>
	virtual bool IsNoMag() override;
	/// <summary>
	/// 磁力をNにする弾を発射する判定
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagShotN() override;
	/// <summary>
	/// 磁力をNにする弾を発射する判定
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagShotS() override;
	/// <summary>
	/// Pad番号の設定
	/// <para>こいつで初期化、更新するPadを設定してください。</para>
	/// </summary>
	/// <param name="padNum"></param>
	bool IsTriStart();
private:
	int m_PadNum = 0;		//Pad番号
};

