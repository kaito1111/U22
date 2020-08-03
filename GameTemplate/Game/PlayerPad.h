/// <summary>
/// Playerパッド
/// 拡張 : photonサーバーにPadデータを送る必要性。
/// </summary>

#pragma once
#include "IPad.h"

class PlayerPad : public IPad
{
public:
	//コンストラクタ
	PlayerPad();

	/// <summary>
	/// 更新
	/// <para>photonにデータ転送</para>
	/// </summary>
	virtual void Update() override;
};

