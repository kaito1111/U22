#pragma once
class GamePlayer;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void SetDec(float d) {
		Decline = d;
	}
private:
	int	m_PlayerNum			= 0;
	bool Start()override;
	void Update()override;
	GamePlayer*	m_Player[4]			= {};
	float Decline				= 0.0f;		//���̌��E
};