#include "stdafx.h"
#include "stageObject1.h"
#include "Player.h"

stageObject1::stageObject1()
{
	//ドッスン棘やで。

	//cmoファイルの読み込み
	m_model.Init(L"Assets/modelData/TogeToge.cmo");
	m_characon.Init(250.0f, 125.0f, m_position);
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
	float DownSpeed = -200.0f;	//落下速度
	float UpSpeed = 77.0f;		//上昇速度
	timer++;				//落下後ちょっと止めるやつ

	//上下運動
	if (m_position.y >= 1880
		&& timer >= 1200&&
		UpDown == false) {
		moveSpeed.y = DownSpeed;

		//落下しきったとき
		if (m_position.y <= 3400
			&&UpDown == false) {
			timer = 0;
			UpDown = true;
		}

	}
	if (m_position.y<=1880
		&&UpDown == true) {
		moveSpeed.y = UpSpeed;
		if (m_position.y >= 3400) {
			timer = 0;
			UpDown = false;
		}
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