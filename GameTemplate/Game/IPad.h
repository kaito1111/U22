/// <summary>
/// ���Pad�N���X
/// </summary>

#pragma once
#include "HID/Pad.h"
#include "GameObject/IGameObject.h"

class IPad : public IGameObject{
public:
	/// <summary>
	/// Pad�̏�����
	/// </summary>
	/// <param name="PadNum"></param>
	virtual void Init(int PadNum)
	{
		//�p�b�h�̏�����
		g_Pad[PadNum].Init(PadNum);
		m_PadNum = PadNum;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	virtual bool IsJump()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonA)) {
			//A
			return true;
		}
		return false;
	}

	virtual bool IsMagN()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonX)) {
			//X
			return true;
		}
		return false;
	}

	virtual bool IsMagS()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonY)) {
			//Y
			return true;
		}
		return false;
	}

	virtual bool IsNoMag()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonB)) {
			//B
			return true;
		}
		return false;
	}

	virtual bool IsMagShotN()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonRB1)) {
			//RB1
			return true;
		}
		return false;
	}

	virtual bool IsMagShotS()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonLB1)) {
			//LB1
			return true;
		}
		return false;
	}

	virtual bool IsTriStart()
	{
		if (g_Pad[m_PadNum].IsPress(enButtonStart)) {
			//start
			return true;
		}
		return false;
	}

	virtual float& MoveX()
	{
		vX = g_Pad[m_PadNum].GetLStickXF();
		return vX;
	}
	virtual float& MoveZ()
	{
		vZ = g_Pad[m_PadNum].GetLStickYF();
		return vZ;
	}

	int& getPlayerNum()
	{
		return m_PadNum;
	}


	//�p�����Ă��ł͎g����悤��
	//Get�֐���������������H
protected:
	int m_PadNum = 0;		//Pad�ԍ� 0=p1 1=p2
	bool A, B, X, Y, RB1, LB1;	//�{�^�� �����������ق�����������Get�Ă΂��܂Œl�g���ł���( ߄D�)
	float vX = 0.0f;
	float vZ = 0.0f;
};
