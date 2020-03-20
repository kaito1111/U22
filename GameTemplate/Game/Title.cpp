#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "stageObjectJenerator.h"
Title::Title()
{
}


Title::~Title()
{
	
}

bool Title::Start()
{
	
	m_model.Init(L"Asset/modelData/stage_oreore.cmo");
	m_model2.Init(L"Asset/modelData/stageDossun.cmo");
	return true;
}

void Title::Update()
{
	stageSelect();
	
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_scale);
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);

	//nowStageをジェネレーターに渡して、その数字に応じてNewGOさせる
	if (GetAsyncKeyState('K')) {
		NewGO<Game>(1);
		generator->setStageNum(nowStage);
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
	//右が押されたときに左送りにする
	if(nowStage == 0					//自分の番号以上
		||nowStage == -1				//自分の数字より１つ小さい
		&&m_pos.x > LLimit				//端に行っているかどうか
		&&RStageChange == true){		//右が押された
		m_pos.x -= moveSpeed;			//動かす
			if (m_pos.x <= -LLimit) {
				m_pos.x = -LLimit;
				RStageChange = false;
			}
	}
	//左が押されたときに右送りにする
	if (nowStage >= 0					//自分の番号以下
		|| nowStage == 1				//自分の数字より1つ大きい
		&& m_pos.x < RLimit			    //端に行っているかどうか
		&& LStageChange == true) {		//左が押された
		m_pos.x += moveSpeed;			//動かす
		if (m_pos.x <= -RLimit) {
			m_pos.x = -RLimit;
			LStageChange = false;
		}
	}
	//自分の番号じゃなくなったとき、小さくする

	if (nowStage != 0 && m_scale.x > 0) {
		m_scale.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 0 && m_scale.y > 0) {
		m_scale.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 0 && m_scale.z > 0) {
		m_scale.z -= scaleChangeSpeed.z;
	}
	////////////////////////////////////////////////////////////////////
	//ステージ2
	//右が押されたときに左送りにする
	if (nowStage == 1					//自分の番号以上
		|| nowStage == 0				//自分の数字より１つ小さい
		&& m_pos2.x > LLimit			//端に行っているかどうか
		&&RStageChange == true) {		//右が押された
		m_pos2.x -= moveSpeed;			//動かす
		if (m_pos2.x <= -LLimit) {
			m_pos2.x = -LLimit;
			RStageChange = false;
		}
	}
	//左が押されたときに右送りにする
	if (nowStage >= 1					//自分の番号以下
		|| nowStage == 2				//自分の数字より1つ大きい
		&& m_pos2.x < RLimit			//端に行っているかどうか
		&& LStageChange == true) {		//左が押された
		m_pos2.x += moveSpeed;			//動かす
		if (m_pos2.x <= -RLimit) {
			m_pos2.x = -RLimit;
			LStageChange = false;
		}
	}
	//自分の番号じゃなくなったとき、小さくする
	if (nowStage != 1 && m_scale2.x > 0) {
		m_scale2.x -= scaleChangeSpeed.x;
	}
	if (nowStage != 1 && m_scale2.y > 0) {
		m_scale2.y -= scaleChangeSpeed.y;
	}
	if (nowStage != 1 && m_scale2.z > 0) {
		m_scale2.z -= scaleChangeSpeed.z;
	}
}