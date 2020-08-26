#include "stdafx.h"
#include "moveFloor.h"
#include "Player.h"
#include"Gimmick_Button.h"
moveFloor::moveFloor(/*const wchar_t * modelName, CVector3 pos, CQuaternion rot*/)
{
	/*m_model.Init(modelName);
	m_pos = pos;
	m_rot = rot;*/
	m_Se.Init(L"Assets/sound/moveFloor.wav");
	m_Se.SetVolume(0.5f);
}

moveFloor::~moveFloor()
{
}

void moveFloor::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool moveFloor::Start()
{
	m_player = FindGO<GamePlayer>("player1");
	m_player2 = FindGO<GamePlayer>("player2");
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/moveFloor.cmo");
	//m_pos = { 0.0f,100.0f,0.0f };
	int MaxPlayer = Pad::CONNECT_PAD_MAX;

	startPos = m_pos;
	//up = m_pos.y + 100;
	//down = m_pos.y - 100;
	m_BoxCharaCon.Init(100.0f, 20.0f, 1.0f, m_pos);//箱オブジェクト
	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	return true;
}

void moveFloor::Update()
{
	//メッシュの云々。要するに当たり判定
	//Move();
	move2();
	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void moveFloor::Move()
{
	//const float startUpLimit = 5;  //最初のスピードの上限
	const float speedUPLimit = 7;  //スピードの上限
	const float speedDownLimit = 0;//スピードの下限
	const float speed = 0.1;
	//下降
	if (UDPos == false) {

		//加速
		if (speedDown == false) {
			moveSpeed += speed;
			//一定値まで行ったら加減速フラグを切り替える
			if (moveSpeed >= speedUPLimit) {
				speedDown = true;
			}
		}

		//減速
		if (speedDown == true) {
			moveSpeed -= speed;

			if (moveSpeed <= speedDownLimit) {
				speedDown = false;				//一定値まで行ったらフラグを切り替える。
				UDPos = true;					//下がり切っているので上昇下降フラグも切り替える
				moveSpeed = speedDownLimit;		//スピードを0に合わせる

			}
		}
		m_pos.y += moveSpeed;
	}

	//上昇
	if (UDPos == true) {

		//加速
		if (speedDown == false) {
			moveSpeed += speed;
			//一定値まで行ったらフラグを切り替える
			if (moveSpeed >= speedUPLimit) {
				speedDown = true;

			}
		}

		//減速
		if (speedDown == true) {
			moveSpeed -= speed;
			//一定値まで行ったらフラグを切り替える
			if (moveSpeed <= speedDownLimit) {
				speedDown = false;
				UDPos = false;
				moveSpeed = speedDownLimit;
			}
		}
		m_pos.y -= moveSpeed;
	}
}

void moveFloor::move2()
{
	const float movespeed = 4;
	float y = m_pos.y;
	//上昇
	if (y <= up && udlimit == false) {
		y += movespeed;
	}
	if (y >= up) {
		m_Se.Play(true);
		udlimit = true;
	}
	//下降
	if (y >= down && udlimit == true) {
		y -= movespeed;
	}
	if (down >= y) {
		m_Se.Play(true);
		udlimit = false;
	}
	CVector3 MoveSpeed = { 0.0f,y,0.0f };
	//m_pos.y = y;
	playerMove();
	m_pos = m_BoxCharaCon.Execute(1.0f, MoveSpeed);

}

void moveFloor::playerMove()
{
	CVector3 pl1pos = m_player->GetPosition();
	float diffY = m_pos.y - pl1pos.y;
	float diffX = m_pos.x - pl1pos.x;
	if (0.0f <= diffY <= 1.0f&&
		fabsf(diffX) <= m_BoxCharaCon.GetWide()) {
		m_player->SetPosition(pl1pos, { 0.0f,moveSpeed,0.0f });
	}
	CVector3 pl2pos = m_player2->GetPosition();
	diffY = m_pos.y - pl2pos.y;
	diffX = m_pos.x - pl2pos.x;
	if (0.0f <= diffY <= 1.0f&&
		fabsf(diffX) <= m_BoxCharaCon.GetWide()) {
		m_player2->SetPosition(pl2pos, { 0.0f,moveSpeed,0.0f });
	}
}