/// <summary>
/// Player�p�b�h
/// �g�� : photon�T�[�o�[��Pad�f�[�^�𑗂�K�v���B
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
	/// <para>photon�Ƀf�[�^�]��</para>
	/// </summary>
	virtual void Update() override;
};

