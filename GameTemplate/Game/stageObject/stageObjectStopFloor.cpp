#include "stdafx.h"
#include "stageObjectStopFloor.h"
#include "Player.h"
#include"Floor.h"


stageObjectStopFloor::stageObjectStopFloor(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/)
{
	/*m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;*/
}

stageObjectStopFloor::~stageObjectStopFloor()
{
	DeleteGO(floor);
}

bool stageObjectStopFloor::Start()
{
	floor = NewGO<Floor>(1);
	m_player[0] = FindGO<Player>("player1");
	m_player[1] = FindGO<Player>("player2");
	m_model.Init(L"Assets/modelData/aStopFloor");//通る前のモデル
	return true;
}

void stageObjectStopFloor::Update()
{
	//プレイヤーのポジションを取得
	playerPosition1 = m_player[0]->GetPosition();
	playerPosition2 = m_player[1]->GetPosition();

	//プレイヤーが両方下にいるとき、フラグをfalseにする。
	if (playerPosition1.y < m_pos.y
		&& playerPosition2.y < m_pos.y) {
		upFlag = false;
	}
	//自分の座標より上に行ったらフラグ切り替え
	if (playerPosition1.y > m_pos.y 
		|| playerPosition2.y > m_pos.y) {
		upFlag = true;
	}
	//フラグ切り替わったからモデルNewGO。フラグを戻す
	if (upFlag == true&&NewGOModel == false) {
		floor = NewGO<Floor>(1);
		NewGOModel = true;
	}
	//プレイヤーが両方下に行ったとき、モデルを破棄する
	if (upFlag == false && NewGOModel == true) {
		DeleteGO(floor);
		NewGOModel = false;
	}
}
