/// <summary>
/// Player�p�b�h
/// </summary>

#pragma once
#include "IPad.h"

class PlayerPad : public IPad
{
public:
	//�R���X�g���N�^
	PlayerPad();
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() override;
};

