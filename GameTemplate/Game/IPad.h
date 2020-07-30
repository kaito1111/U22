/// <summary>
/// 基底Padクラス
/// </summary>

#pragma once
#include "HID/Pad.h"
#include "GameObject/IGameObject.h"

class IPad /*: public IGameObject*/{
public:
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// ジャンプの入力
	/// </summary>
	/// <returns></returns>
	virtual bool IsJump() = 0;
	/// <summary>
	/// 磁力を変える入力
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagN() = 0;
	virtual bool IsMagS() = 0;
	virtual bool IsNoMag() = 0;
	virtual bool IsMagShotN() = 0;
	virtual bool IsMagShotS() = 0;
	virtual float& MoveX() = 0;
	virtual float& MoveZ() = 0;
};
