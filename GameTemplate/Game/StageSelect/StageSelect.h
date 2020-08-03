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
	SpriteRender m_sprite;             //�X�v���C�g
	CVector2 m_spritePos;              //�X�v���C�g�̍��W�B
	bool LStageChange = false;          //�X�e�[�W��؂�ւ���t���O
	bool RStageChange = false;
	int count = 0;
	const CVector3 littleScale = { 0.1f,0.1f,0.1f };//�I�΂�ĂȂ��X�e�[�W�̃T�C�Y
	const CVector3 halfScale = { 0.5f,0.5f,0.5f };
};