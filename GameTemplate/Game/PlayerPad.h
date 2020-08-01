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
	/// 更新
	/// </summary>
	virtual void Update() override;
};

