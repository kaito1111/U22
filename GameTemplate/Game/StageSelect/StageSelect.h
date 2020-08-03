#pragma once
class stageObjectJenerator;
class TitleStage;
class TitleCamera;
class Game;
class Stage;
class GamePlayer;
class StageSelect : public IGameObject
{
public:
	StageSelect();
	~StageSelect();
	bool Start();
	void Update();
	void stageSelect();
private:
	//GamePlayer* player1 = nullptr;
	//GamePlayer* player2 = nullptr;
	Stage* stage = nullptr;
	Game* game = nullptr;
	TitleCamera* titleCamera = nullptr;
	TitleStage* titleStage = nullptr;
	stageObjectJenerator* generator;
	SpriteRender m_sprite;             //スプライト
	CVector2 m_spritePos;              //スプライトの座標。
	bool LStageChange = false;          //ステージを切り替えるフラグ
	bool RStageChange = false;
	int count = 0;
	const CVector3 littleScale = { 0.1f,0.1f,0.1f };//選ばれてないステージのサイズ
	const CVector3 halfScale = { 0.5f,0.5f,0.5f };
};