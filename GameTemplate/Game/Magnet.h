#pragma once
class Magnet
{
private:

	Magnet();
	~Magnet();

	CVector3 MagnetTask();
	enum State {
		NMode,
		SMode,
		NoMode,
		Num,
	};
	State state = NoMode;

	CVector3* m_Position = nullptr;

public:
	const void SetState(State& s) {
		state = s;
	}
	const State GetState() {
		return state;
	}
	const CVector3 GetPosition() {
		return *m_Position;
	}
	const void SetPosition(CVector3* pos){
		m_Position = pos;
	}
};