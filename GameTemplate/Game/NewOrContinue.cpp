#include "stdafx.h"
#include "NewOrContinue.h"
#include "KaitoTask.h"
#include"PlayerData.h"
#include "Stage.h"
#include"StageSelect/StageSelect.h"
#include<tuple>
#include"Game.h"
NewOrContinue::NewOrContinue()
{
}


NewOrContinue::~NewOrContinue()
{
	DeleteGO(m_spriteRender);
}

bool NewOrContinue::Start()
{
	//初期化
	m_spriteRender = NewGO<SpriteRender>(1, "sprite");
	m_spriteRender->Init(L"Assets/sprite/初めからor続きから.dds",1280,720);
	return true;
}

void NewOrContinue::Update()
{
	//int a = 0;
	//最初から（ステージセレクト画面へ）。
	if (g_Pad[0].IsPress(enButtonA)) {
		NewGO<StageSelect>(0, "stageSelect");
		DeleteGO(this);
	}
	//続きから（プレイヤーの座標とステージ番号をロード）
	if (g_Pad[0].IsPress(enButtonX) && padB == true) {
		
		//前回のステージとプレイヤーの座標をロード
		//プレイしていない状態で選択すると、ステージ１と初期位置をロードします
		LoadPlayerData();
		game = NewGO<Game>(0, "game");
		Continue = true;
		game->setCon(Continue);
		game->setAll(player1(), player2(), GetStage());
		DeleteGO(this);
	}
	if (!g_Pad[0].IsTrigger(enButtonB)) {
		padB = true;
	}
}