#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"TitleStage.h"
Title::Title()
{
}


Title::~Title()
{
	DeleteGO(titleStage);
}

bool Title::Start()
{
	titleStage = NewGO<TitleStage>(1);
	return true;
}

void Title::Update()
{
	stageSelect();

	//nowStageをジェネレーターに渡して、その数字に応じてNewGOさせる
	if (GetAsyncKeyState('K')) {
		NewGO<Game>(1);
		generator->setStageNum(nowStage);
		DeleteGO(this);
		
	}

}

void Title::stageSelect()
{
	const float LLimit = -2000;								//左端
	const float RLimit = 2000;								//右端
	const float moveSpeed = 100;							//動く速度
	const CVector3 scaleChangeSpeed = {0.05, 0.05, 0.05};   //拡縮速度
	//ステージ切り替えのフラグ変更
	if (GetAsyncKeyState('D') && nowStage <stageMax) {
		RStageChange = true;
		nowStage++;
	}
	if (GetAsyncKeyState('A')&&nowStage > 0) {
		LStageChange = true;
		nowStage--;
	}
	////////////////////////////////////////////////////////////////
	//ステージ１
	//stage1の情報
	CVector3 pos1 = titleStage->GetPos();
	CVector3 scale1 = titleStage->GetScale();
	//右が押されたときに左送りにする
	if(nowStage == 0					//自分の番号以上
		||nowStage == -1				//自分の数字より１つ小さい
		&& pos1.x > LLimit				//端に行っているかどうか
		&&RStageChange == true){		//右が押された
		pos1.x -= moveSpeed;			//動かす
			if (pos1.x <= -LLimit) {
				pos1.x = -LLimit;
				RStageChange = false;
			}
	}
	//左が押されたときに右送りにする
	if (nowStage >= 0					//自分の番号以下
		|| nowStage == 1				//自分の数字より1つ大きい
		&& pos1.x < RLimit			    //端に行っているかどうか
		&& LStageChange == true) {		//左が押された
		pos1.x += moveSpeed;			//動かす
		if (pos1.x <= -RLimit) {
			pos1.x = -RLimit;
			LStageChange = false;
		}
	}
	//自分の番号じゃなくなったとき、小さくする
	

	if (nowStage != 0 && pos1.x > 0) {
		scale1.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 0 && pos1.y > 0) {
		scale1.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 0 && pos1.z > 0) {
		scale1.z -= scaleChangeSpeed.z;
	}
	////////////////////////////////////////////////////////////////////
	//ステージ2
	//stage2の情報
	CVector3 pos2 = titleStage->GetPos2();
	CVector3 scale2 = titleStage->GetScale2();
	//右が押されたときに左送りにする
	if (nowStage == 1					//自分の番号以上
		|| nowStage == 0				//自分の数字より１つ小さい
		&& pos2.x > LLimit			//端に行っているかどうか
		&&RStageChange == true) {		//右が押された
		pos2.x -= moveSpeed;			//動かす
		if (pos2.x <= -LLimit) {
			pos2.x = -LLimit;
			RStageChange = false;
		}
	}
	//左が押されたときに右送りにする
	if (nowStage >= 1					//自分の番号以下
		|| nowStage == 2				//自分の数字より1つ大きい
		&& pos2.x < RLimit			//端に行っているかどうか
		&& LStageChange == true) {		//左が押された
		pos2.x += moveSpeed;			//動かす
		if (pos2.x <= -RLimit) {
			pos2.x = -RLimit;
			LStageChange = false;
		}
	}
	//自分の番号じゃなくなったとき、小さくする
	if (nowStage != 1 && scale2.x > 0) {
		scale2.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 1 && scale2.y > 0) {
		scale2.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 1 && scale2.z > 0) {
		scale2.z -= scaleChangeSpeed.z;
	}

	//各ステージの情報を更新
	titleStage->SetPos(pos1);
	titleStage->SetPos(pos2);
	titleStage->SetScale(scale1);
	titleStage->SetScale(scale2);
}