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
	//DeleteGO(titleStage);
	DeleteGO(titleCamera);
}

bool StageSelect::Start()
{
	m_Stage1_sprite = NewGO<SpriteRender>(0);
	m_Stage1_sprite->Init(L"Assets/sprite/Corse1_image.dds", 200.0f, 200.0f,true);
	m_Stage1_sprite->SetPosition(m_Stage1_spritePos);

	//m_Stage1_sprite = NewGO<SpriteRender>(0);
	//m_Stage1_sprite->Init(L"Assets/sprite/Corse1_image.dds", 500.0f, 500.0f);
	//m_Stage1_sprite->SetPosition(m_Stage1_spritePos);

	m_StageModel = NewGO<SkinModelRender>(0);
	m_StageModel->Init(L"serectStage.cmo");
	m_StageModel->SetPosition(CVector3::Zero());
	m_staticObj.CreateMeshObject(m_StageModel->GetSkinModel(), CVector3::Zero(), CQuaternion::Identity());
	titleCamera = NewGO<TitleCamera>(1);

	m_PlayerModel = NewGO<SkinModelRender>(0);
	m_PlayerModel->Init(L"Player.cmo");
	m_CharaCon.Init(40.0f, 20.0f, m_PlayerPos);
	//titleStage = NewGO<TitleStage>(1);
	return true;
}

void StageSelect::Update()
{
	//stageSelect();
	PlayerMove();
	//nowStageをジェネレーターに渡して、その数字に応じてNewGOさせる
	//if (GetAsyncKeyState('K')) {
	//	game = NewGO<Game>(1,"game");
	//	stage = NewGO<Stage>(1,"stage");
	//	stage->setStageNum(0);

	//	DeleteGO(this);
	//	
	//}
	
}

void StageSelect::stageSelect()
{
	//const int stageMax = 2;			//ステージの数.上限
	//const float LLimit = 4000;		//左端
	//const float RLimit = 0;			//右端
	//const float moveSpeed = 100;	//動く速度
	//const CVector3 scaleChangeSpeed = {0.05, 0.05, 0.05};   //拡縮速度
	
	//count++;
	//if (GetAsyncKeyState('D') && nowStage <stageMax&&count >= 120) {//ステージ切り替えのフラグ変更
	//	RStageChange = true;
	//	nowStage++;
	//	count = 0;
	//}
	//if (GetAsyncKeyState('A')&&nowStage > 0 && count >= 120) {
	//	LStageChange = true;
	//	nowStage--;
	//	count = 0;
	//}
	//ステージ番号が0より小さくなった時、０にする
	//if (nowStage < 0) {
	//	nowStage = 0;
	//}
	////ステージ番号が最大値より大きくなった時、最大値を突っ込む
	//if (nowStage > stageMax) {
	//	nowStage = stageMax;
	//}

	//ステージⅠ
	//CVector3 pos1 = titleStage->GetPos();
	//CVector3 scale1 = titleStage->GetScale();
	
	//if (nowStage == 0 && scale1.x<1) {
	//	scale1 += scaleChangeSpeed;
	//}
	//if (nowStage != 0&&scale1.x>0) {
	//	scale1 -= scaleChangeSpeed;
	//}
	//ステージⅡ
	//CVector3 pos2 = titleStage->GetPos2();
	//CVector3 scale2 = titleStage->GetScale2();
	//if (nowStage == 1) {
	//	scale2 += scaleChangeSpeed;
	//}
	//if (nowStage != 1) {
	//	scale2 -= scaleChangeSpeed;
	//}
	////各ステージの情報を更新
	////ステージ１
	//titleStage->SetPos(pos1);
	//titleStage->SetScale(scale1);
	////ステージ2
	//titleStage->SetPos2(pos2);
	//titleStage->SetScale2(scale2);
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
	float jump = g_Pad[0].IsTrigger(enButtonA);
	m_CharaCon.Execute(1.0f, { MoveX,0.0f,0.0f });
	m_PlayerRot.SetRotationDeg(CVector3::AxisY(), m_angle);
	m_PlayerModel->SetPRS(m_PlayerPos, m_PlayerRot, CVector3::One());
}
