/// <summary>
/// �l�b�g���[�N�p�b�h
/// �g�� : photon�T�[�o�[����Pad�f�[�^����M�B
/// </summary>

#pragma once
#include "IPad.h"
class NetworkPad : public IPad
{
public:
	//�R���X�g���N�^
	NetworkPad();
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() override;
};

