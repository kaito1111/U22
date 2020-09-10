#pragma once
class GamePlayer;
#include "character/CharacterController.h"
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void SetDec(float d) {
		Decline = d;
	}
private:
	CharacterController m_CharaCon;
	int	m_PlayerNum			= 0;
	bool Start()override;
	void Update()override;
	GamePlayer*	m_Player[2]			= {};
	float Decline				= 0.0f;		//‰º‚ÌŒÀŠE
	CVector3 m_Pos = CVector3::Zero();
};