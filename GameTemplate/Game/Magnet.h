#pragma once
class Magnet
{
private:

	Magnet();
	~Magnet();

	void MagnetTask();
	enum State {
		NMode,
		SMode,
		NoMode,
		Num,
	};
	State state = NoMode;

	CVector3* m_Position = nullptr;
	CQuaternion* m_Rot = nullptr;

public:
	const void SetState(State& s) {
		state = s;
	}
	const State GetMagnet() {
		return state;
	}
	const CVector3 GetPosition() {
		return *m_Position;
	}
};