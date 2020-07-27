#include "stdafx.h"
#include "NewOrContinue.h"
#include "KaitoTask.h"
#include"PlayerData.h"
#include "Stage.h"
#include"StageSelect/StageSelect.h"
NewOrContinue::NewOrContinue()
{
}


NewOrContinue::~NewOrContinue()
{
	DeleteGO(m_spriteRender);
}

bool NewOrContinue::Start()
{
	
	m_spriteRender = NewGO<SpriteRender>(1, "sprite");
	m_spriteRender->Init(L"Assets/sprite/初めからor続きから.dds",1280,720);
	return true;
}

void NewOrContinue::Update()
{

	//最初から（ステージセレクト画面へ）。
	if (g_Pad[0].IsTrigger(enButtonA)) {
		NewGO<StageSelect>(0, "stageSelect");
		DeleteGO(this);
	}
	//続きから（プレイヤーの座標とステージ番号をロード）
	//if (g_Pad[0].IsTrigger(enButtonA)) {
	//	//前回のステージとプレイヤーの座標をロード

	//}
}
