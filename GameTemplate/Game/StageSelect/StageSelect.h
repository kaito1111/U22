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

private:
	void stageSelect();
	void PlayerMove();
	void SetCameraTarget();
	void SelectSprite();

	TitleCamera* m_TitleCamera = nullptr;

	SpriteRender* m_Stage1Sprite = nullptr;             //スプライト
	SpriteRender* m_Stage2Sprite = nullptr;
	CVector3 m_Stage1SpritePos = { 0.0f,100.0f ,0.0f };              //スプライトの座標。
	CVector3 m_Stage2SpritePos = { 0.0f,0.0f ,0.0f };

	SkinModelRender* m_StageModel = nullptr;
	PhysicsStaticObject m_staticObj;

	SpriteRender* m_SelectSprite = nullptr;
	CVector3 m_SelectSpritePos = CVector3::Zero();
	float m_SelectLen = 20.0f;

	SkinModelRender* m_PlayerModel = nullptr;
	CVector3 m_PlayerPos = CVector3::Zero();
	CQuaternion m_PlayerRot = CQuaternion::Identity();
	float m_angle = 0.0f;
	bool m_Right = true;
	CharacterController m_CharaCon;
};