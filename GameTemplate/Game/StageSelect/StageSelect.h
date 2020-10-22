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

	//CVector3 GetPos() const
	//{
	//	return m_pos[0];
	//}
private:
	void stageSelect();
	void PlayerMove();
	//Sprite m_copyMainRtToFrameBufferSprite;	//�Ȃ񂩗v�郄�c
	//SkinModel m_stage[g_StageMAX] = {};
	//CVector3 m_pos[g_StageMAX] = {};
	//Player* player1 = nullptr;
	//Player* player2 = nullptr;
	//Stage* stage = nullptr;
	//Game* game = nullptr;
	TitleCamera* titleCamera = nullptr;
	//TitleStage* titleStage = nullptr;
	//stageObjectJenerator* generator;
	SpriteRender* m_Stage1_sprite = nullptr;             //�X�v���C�g
	SpriteRender* m_Stage2_sprite = nullptr;
	CVector3 m_Stage1_spritePos = { 0.0f,100.0f ,0.0f };              //�X�v���C�g�̍��W�B
	CVector3 m_Stage2_spritePos = { 0.0f,0.0f ,0.0f };
	SkinModelRender* m_StageModel = nullptr;
	PhysicsStaticObject m_staticObj;
	
	SkinModelRender* m_PlayerModel = nullptr;
	CVector3 m_PlayerPos = CVector3::Zero();
	CQuaternion m_PlayerRot = CQuaternion::Identity();
	float m_angle = 0.0f;
	bool m_Right = true;
	CharacterController m_CharaCon;
	//bool LStageChange = false;          //�X�e�[�W��؂�ւ���t���O
	//bool RStageChange = false;
	//int count = 0;
	//const CVector3 littleScale = { 0.1f,0.1f,0.1f };//�I�΂�ĂȂ��X�e�[�W�̃T�C�Y
	//const CVector3 halfScale = { 0.5f,0.5f,0.5f };
};