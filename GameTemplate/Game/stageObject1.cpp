#include "stdafx.h"
#include "stageObject1.h"
#include "Player.h"

stageObject1::stageObject1()
{
	
}

stageObject1::~stageObject1()
{
	
}

bool stageObject1::Start()
{
	//ドッスン棘やで。

	//cmoファイルの読み込み
	m_model.Init(L"Assets/modelData/TogeToge.cmo");
	m_characon.Init(100.0f, 0.0f, m_position);
	player = FindGO<Player>("player");
	return true;
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
	float DownSpeed = -100.0f;	//落下速度
	float UpSpeed = 20.0f;		//上昇速度
	timer++;				//落下後ちょっと止めるやつ

	//上下運動
	if (m_position.y >= 1880
		//&& timer >= 120
		&&UpDown == false) {
		moveSpeed.y = DownSpeed;
	}

	//落下しきったとき
	if (m_position.y <= 1900
		&& UpDown == false) {
		UpDown = true;
		timer = 0;
	}

	//落ちた後は昇るよ。まさに昇竜拳。
	if (m_position.y <= 3400
		&&UpDown == true
		//&&timer >= 120
		) {
		moveSpeed.y = UpSpeed;
		
	}
	if (m_position.y >= 3300) {
		//timer = 0;
		UpDown = false;
	}
	m_position = m_characon.Execute(1.0f, moveSpeed);

	//プレイヤーを殺す処理

	CVector3 PPos = player->GetPosition();
	CVector3 ToP = PPos - m_position;
	if (ToP.y <= 50 && ToP.y-50			//プレイヤーからのベクトルYのみを取る
		&&ToP.x >=-50 && ToP.x <= 50) {//     　　　　〃　　　　　Xのみを取る
		//ここにプレイヤーを殺す処理かな
		CVector3 CheckPoint = CVector3::Zero();

		//後でチェックポイントを作る
		player->SetPosition(CheckPoint);
	}


}

void stageObject1::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}