#include "stdafx.h"
#include "StageSelect/StageSelect.h"
#include "Game.h"
#include "stageObjectJenerator.h"
#include"StageSelect/TitleStage.h"
#include"StageSelect/TitleCamera.h"
#include"Stage.h"
#include<vector>
#include "../CheckPointgenerator.h"
#include <iostream>
#include"Game.h"
StageSelect::StageSelect()
{
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	int a = 0;
}

StageSelect::~StageSelect()
{
	//DeleteGO(titleStage);
	DeleteGO(titleCamera);
	
}

bool StageSelect::Start()
{
	static const float width3 = 10000.0f;//横幅
	static const float halfWidth = width3 /2;//半分

	titleCamera = NewGO<TitleCamera>(1);
	for (int nowInitStage = 0; nowInitStage < g_StageMAX; nowInitStage++)
	{
		//L""のLはwchar_t型がどうか判断するためのヤツ

		//ステージのテクスチャ張った板ポリを出してます。
			wchar_t stagePath[256] = {};
			swprintf(stagePath, L"Assets/modelData/titleStage%d.cmo", nowInitStage + 1);
			m_stage[nowInitStage].Init(stagePath);
			if (nowInitStage == 0) {
				m_pos[nowInitStage] = CVector3::Zero();
				//m_pos[nowInitStage].x += halfWidth;
			}
			else {
				m_pos[nowInitStage] = CVector3::Zero();
				m_pos[nowInitStage].x -= width3 * nowInitStage;
			}
			int a = 0;
			
	}

	/*titleStage = NewGO<TitleStage>(1);
	player1 = FindGO<Player>("player1");
	player2 = FindGO<Player>("player2");*/

	return true;
}

void StageSelect::Update()
{
	//ステージとKaitoTaskクラスをNewGOする。つかゲーム画面に移行する。
	if (g_Pad->IsTrigger(enButtonA))
	{
		game = NewGO<Game>(0, "game");
		game->SetStage(titleCamera->GetChoiceStageNum());
		CheckPointgenerator* PointGenerator = NewGO< CheckPointgenerator>(0, "checkpointgenerator");
		wchar_t pointGeneratorNum[256] = {};
		swprintf(pointGeneratorNum, L"Assets/level/Corse_Level_%d.tkl",titleCamera->GetChoiceStageNum()+1);
		PointGenerator->Load(pointGeneratorNum);
		DeleteGO(this);
	}
	
	for (int i = 0; i < g_StageMAX; i++) {
		m_stage[i].UpdateWorldMatrix(m_pos[i], CQuaternion::Identity(), CVector3::One()*10.0f);
		m_stage[i].Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}

void StageSelect::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}

void StageSelect::Draw()
{
	for (int i = 0; i < g_StageMAX; i++) {
		m_stage[i].Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}
