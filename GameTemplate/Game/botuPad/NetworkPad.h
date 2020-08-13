/// <summary>
/// ネットワークパッド
/// 拡張 : photonサーバーからPadデータを受信。
/// </summary>

#pragma once
#include "IPad.h"
class NetworkPad : public IPad
{
public:
	//コンストラクタ
	NetworkPad();
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() override;
};

