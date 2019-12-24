#include "stdafx.h"
#include "stageObject1.h"
#include "Player.h"

stageObject1::stageObject1()
{
	//ドッスン棘やで。

	//cmoファイルの読み込み
	m_model.Init(L"Assets/modelData/TogeToge.cmo");
	m_characon.Init(1200.0f, 540.0f, m_position);
	m_position.y = 5000.0f;
}


stageObject1::~stageObject1()
{
	
}

void stageObject1::Update()
{
	Move();//動かす奴.

	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());

}



void stageObject1::Move()
{

	CVector3 moveSpeed = CVector3::Zero();//移動速度
	float Down = -200.0f;	//落下速度
	float Up = 77.0f;		//上昇速度
	timer++;				//落下後ちょっと止めるやつ

	int a = 1;//条件文の代わりに突っ込むやつ。後で消す。

	if (a == 1/*一定より上の時*/
		&& timer >= 120) {
		moveSpeed.y = Down;
		if (a == 1/*落下しきったとき*/
			&& timer == 120) {
			timer = 0;
		}
	}
	if (a == 1/*一定より下に行ったとき*/) {
		moveSpeed.y = Up;
	}
	m_position = m_characon.Execute(1.0f, moveSpeed);
}


void stageObject1::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}