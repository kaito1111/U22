#pragma once

class TwoP_Pad
{
	//using NetworkPad = PlayerPad;
public:
	TwoP_Pad();
	~TwoP_Pad();

	void Update();

	int& GetFrameNum()
	{
		return m_frameNo;
	}

private:
	enum KeyState
	{
		Jump,
		MagN,
		MagS,
		NoMag,
		ShotN,
		ShotS,
		Start
	};

	const int				MAX_BUFFERRING = 1;		//バッファリングする数
	std::size_t				MAX_BUFFERRING_T = 5;
	int m_listSize = 0;
	int						m_frameNo = 0;			//プレイできる状態だった、フレームの数
	int Bufferinged;
};