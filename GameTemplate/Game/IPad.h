/// <summary>
/// ���Pad�N���X
/// </summary>

#pragma once
#include "HID/Pad.h"
#include "GameObject/IGameObject.h"

class IPad /*: public IGameObject*/{
public:
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �W�����v�̓���
	/// </summary>
	/// <returns></returns>
	virtual bool IsJump() = 0;
	/// <summary>
	/// ���͂�ς������
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
