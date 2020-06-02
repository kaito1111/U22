#include "stdafx.h"
#include "StageSelect/StageSelect.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"StageSelect/TitleStage.h"
#include"StageSelect/TitleCamera.h"
#include"Stage.h"
#include<vector>
#include"Player.h"
using namespace std;
StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
	DeleteGO(titleStage);
	DeleteGO(titleCamera);
}

bool StageSelect::Start()
{
	
	titleCamera = NewGO<TitleCamera>(1);
	titleStage = NewGO<TitleStage>(1);
    player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");
	return true;
}

void StageSelect::Update()
{
	const CVector3 nextPlayer1Position = {0.0f,200.0f,0.0f};
	const CVector3 nextPlayer2Position = {-50.0f,200.0f,0.0f };
	const int stageMax = 2;//ステージの数.上限
	const float stageXSize = -640.0f;//選ぶステージの横幅
	CVector3 pPos = player2->GetPosition();
	if (g_Pad->IsPress(enButtonA)) {

		for (int nowStage = 0; nowStage < stageMax; nowStage++) {
			//プレイヤー1の座標からステージを選びます
			float a = stageXSize * (nowStage + 1);
			float b = stageXSize * nowStage;
			if (pPos.x > a &&//プレイヤーの座標がスプライト右端より小さく
				pPos.x < b) {//左端より大きいとき
				stage = NewGO<Stage>(1, "stage");
				stage->setStageNum(nowStage);
				player1->SetPosition(nextPlayer1Position);
				player2->SetPosition(nextPlayer2Position);
				DeleteGO(this);
			}
		}

	}
	vector<float> stageLength;

}

void StageSelect::stageSelect()
{
	
	//const float moveSpeed = 100;	//動く速度
	//const CVector3 scaleChangeSpeed = {0.5, 0.5, 0.5};   //拡縮速度
	//count++;
	
}