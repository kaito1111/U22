#pragma once
#include "character/CharacterController.h"
class Player;
class NPole;
class SPole : public IGameObject
{
public:

	SPole();
	//êiÇﬁï˚å¸ÇåàÇﬂÇÈ
	void SetMoveDir(CVector3 MoveDir) {
		m_move = MoveDir;
	}
	void SetPosition(CVector3 pos) {
		m_position=pos;
	}
	CVector3 GetPosition() {
		return m_position;
	}
private:

	~SPole();

	bool Start()override;
	void Update()override;
	void Draw()override;

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_move = CVector3::Zero();
	Player* m_player = nullptr;
	NPole* m_npole = nullptr;
	CharacterController m_characon;

	void deleteRange();
	void magunetTask();
	void idou();
};