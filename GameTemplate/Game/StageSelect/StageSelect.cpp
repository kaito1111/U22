#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"TitleStage.h"
#include"TitleCamera.h"
#include"Stage.h"
StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
	DeleteGO(m_TitleCamera);
}

bool StageSelect::Start()
{
	m_Stage1Sprite = NewGO<SpriteRender>(1);
	m_Stage1Sprite->Init(L"Assets/sprite/Corse1_image.dds", 200.0f, 200.0f,true);
	m_Stage1Sprite->SetPosition(m_Stage1SpritePos);

	m_StageModel = NewGO<SkinModelRender>(0);
	m_StageModel->Init(L"serectStage.cmo");
	m_StageModel->SetPosition(CVector3::Zero());
	m_staticObj.CreateMeshObject(m_StageModel->GetSkinModel(), CVector3::Zero(), CQuaternion::Identity());

	m_TitleCamera = NewGO<TitleCamera>(1);

	m_PlayerModel = NewGO<SkinModelRender>(0);
	m_PlayerModel->Init(L"Player.cmo");
	m_CharaCon.Init(40.0f, 20.0f, m_PlayerPos);

	m_SelectSprite = NewGO<SpriteRender>(0);
	m_SelectSprite->Init(L"Assets/sprite/Yellow.dds", 250.0f, 250.0f);
	m_SelectSprite->SetW(0.0f);

	return true;
}

void StageSelect::Update()
{
	PlayerMove();
	SelectSprite();
	SetCameraTarget();
	stageSelect();
}

void StageSelect::stageSelect()
{
	if (g_Pad[0].IsPress(enButtonB)) {
		Game* m_Game = NewGO<Game>(0,"game");
		CVector3 diff1 = m_PlayerPos - m_Stage1SpritePos;
		CVector3 diff2 = m_PlayerPos - m_Stage2SpritePos;
		if (diff1.Length() > m_SelectLen) {
			m_Game->SetStage(0);
		}
		else if (diff2.Length() > m_SelectLen) {
			m_Game->SetStage(2);
		}
	}
}

void StageSelect::PlayerMove()
{
	float MoveX = g_Pad[0].GetLStickXF()* -10.0f;
	m_PlayerPos.x += MoveX;
	if (MoveX > 0.0001f) {
		m_Right = false;
	}
	if (MoveX < 0.0001f) {
		m_Right = true;
	}
	if (m_Right
		&&m_angle<90.0f
		) {
		m_angle += 10.0f;
	}
	if(
		!m_Right
		&&m_angle>-90.0f
		) {
		m_angle -= 10.0f;
	}
	float jump = 0;
	if (m_CharaCon.IsOnGround()) {
		jump = g_Pad[0].IsTrigger(enButtonA)*15.0f;
	}
	jump -= 0.8f;
	m_CharaCon.Execute(1.0f, CVector3( MoveX, jump,0.0f ));
	m_PlayerRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_PlayerModel->SetPRS(m_PlayerPos, m_PlayerRot, CVector3::One());
}

void StageSelect::SetCameraTarget()
{
	m_TitleCamera->SetTarget(m_PlayerPos);
}

void StageSelect::SelectSprite()
{
	//‹——£”äŠr‚µ‚Ä‘I‘ð‚µ‚Ä‚¢‚éŠG‚ðo‚·
	CVector3 diff1 = m_PlayerPos - m_Stage1SpritePos;
	CVector3 diff2 = m_PlayerPos - m_Stage2SpritePos;
	if (diff1.Length() > m_SelectLen) {
		m_SelectSprite->SetPosition(m_Stage1SpritePos);
		m_SelectSprite->SetW(1.0f);
	}
	else if (diff2.Length() > m_SelectLen) {
		m_SelectSprite->SetPosition(m_Stage2SpritePos);
		m_SelectSprite->SetW(1.0f);
	}
	else {
		m_SelectSprite->SetW(0.0f);
	}
}
