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
	/// <para>GameObjectManager���ŊǗ�����Ă���̂ŌĂяo���Ȃ��ł��������B</para>
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// X�������̈ړ�
	/// </summary>
	/// <returns></returns>
	virtual float& MoveX() override
	{
		float X = g_Pad[PadNum].GetLStickXF();
		return X;
	}
	/// <summary>
	/// Z�������̈ړ�
	/// </summary>
	/// <returns></returns>
	virtual float& MoveZ() override
	{
		float Z = g_Pad[PadNum].GetLStickYF();
		return Z;
	}
	/// <summary>
	/// �W�����v����
	/// </summary>
	/// <returns></returns>
	virtual bool IsJump() override;
	/// <summary>
	/// N�ɂɐ؂�ւ�����
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagN() override;
	/// <summary>
	/// S�ɂɐ؂�ւ�����
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagS() override;
	/// <summary>
	/// ���͂Ȃ�������
	/// </summary>
	/// <returns></returns>
	virtual bool IsNoMag() override;
	/// <summary>
	/// ���͂�N�ɂ���e�𔭎˂��锻��
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagShotN() override;
	/// <summary>
	/// ���͂�N�ɂ���e�𔭎˂��锻��
	/// </summary>
	/// <returns></returns>
	virtual bool IsMagShotS() override;
	/// <summary>
	/// Pad�ԍ��̐ݒ�
	/// <para>�����ŏ������A�X�V����Pad��ݒ肵�Ă��������B</para>
	/// </summary>
	/// <param name="padNum"></param>
	void SetNum(int padNum)
	{
		PadNum = padNum;
	}
private:
	int PadNum = 0;		//Pad�ԍ�
};

