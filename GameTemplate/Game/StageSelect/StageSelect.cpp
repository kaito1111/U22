#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include"TitleCamera.h"
#include "Player.h"
#include "Fade.h"
#include "StageSelectSprite.h"

StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
	DeleteGO(m_Player[0]);
	DeleteGO(m_Player[1]);
	DeleteGO(m_TitleCamera);
	DeleteGO(m_StageModel);
	DeleteGO(m_Sprite);
}

bool StageSelect::Start()
{

	m_StageModel = NewGO<SkinModelRender>(0);
	m_StageModel->Init(L"serectStage.cmo");
	m_StageModel->SetPosition(CVector3::Zero());
	m_staticObj.CreateMeshObject(m_StageModel->GetSkinModel(), CVector3::Zero(), CQuaternion::Identity());

	m_TitleCamera = NewGO<TitleCamera>(1);

	m_Player[0] = NewGO<GamePlayer>(0,"player");
	m_Player[0]->SetPosition(CVector3::Zero());
	m_Player[0]->SetPlayerNum(1);

	m_Player[1] = NewGO<GamePlayer>(0, "player");
	m_Player[1]->SetPosition({ 150.0f,0.0f,0.0f });
	m_Player[1]->SetPlayerNum(2);

	m_Sprite = NewGO<StageSelectSprite>(0);
	return true;
}

void StageSelect::Update()
{
	SetCameraTarget();
	if (g_Pad[m_Player[0]->GetPadNo()].IsPress(enButtonB)) {
		//‹——£”äŠr‚µ‚Ä‘I‘ð‚µ‚Ä‚¢‚éŠG‚ðo‚·
		CVector3 diff1 = m_Player[0]->GetPosition() - m_Sprite->GetSpritePos1();
		CVector3 diff2 = m_Player[0]->GetPosition() - m_Sprite->GetSpritePos2();
		if (m_fade == nullptr) {
			if (diff1.Length() < m_SelectLen) {
				m_fade = NewGO<Fade>(0);
				StageNo = 0;
			}
			else if (diff2.Length() < m_SelectLen) {
				m_fade = NewGO<Fade>(0);
				StageNo = 2;
			}
		}
	}
	if (m_fade != nullptr) {
		if (m_fade->GetLengh() < 210.0f) {
			Game* game = NewGO<Game>(0,"game");
			game->SetStage(StageNo);
			DeleteGO(this);
		}
	}	
}

void StageSelect::SetCameraTarget()
{
	m_TitleCamera->SetTarget(m_Player[0]->GetPosition());
}