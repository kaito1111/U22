#pragma once
//class TitleStage;
class GameCamera;
class Player;
class KaitoTask
{
public:
	KaitoTask();
	~KaitoTask();

	//TitleStage*7
	GameCamera* m_GameCamera = nullptr;
	Player* m_Player[2] = {};
};