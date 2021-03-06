#include "stdafx.h"
#include "MoveFloor2.h"


MoveFloor2::MoveFloor2()
{
}


MoveFloor2::~MoveFloor2()
{
}
void MoveFloor2::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

bool MoveFloor2::Start()
{

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/moveFloor2.cmo");
	//m_pos = { 0.0f,100.0f,0.0f };
	int MaxPlayer = Pad::CONNECT_PAD_MAX;
	StartPos = m_pos;

	m_BoxCharaCon.Init(100.0f, 20.0f, 1.0f, m_pos);//箱オブジェクト
	m_BoxCharaCon.SetAffected(false);
	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_Scale);
	return true;
}

void MoveFloor2::Update()
{
	//メッシュの云々。要するに当たり判定
	Move();
	//m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);//静的物理オブジェクト
	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_Scale);
}

void MoveFloor2::Move()
{
	//必要に応じて適当にいじってくだしあ
	const float speedUPLimit = 0;  //スピードの上限
	const float speedDownLimit = -7;//スピードの下限
	const float speed = 0.1;

	//下降とか書いてるけど左右に動くヤツやで。
	//左
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
	}

	//右
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
	}
	CVector3 MoveSpeed = { moveSpeed,0.0f,0.0f };
	m_pos = m_BoxCharaCon.Execute(1.0f, MoveSpeed);
}

void MoveFloor2::Move2()
{
	const float movespeed = 8.0f;
	float y = m_pos.y;
	//上昇
	if (y <= up && udlimit == false) {
		y += movespeed;
	}
	if (y >= up) {
		udlimit = true;
	}
	if (button->IsOn() == false) {
		//下降
		if (y >= down && udlimit == true) {
			y -= movespeed;
		}
		if (down >= y) {
			udlimit = false;
		}
		m_pos.y = y;
	}
	if (button->IsOn() == true) {
		m_pos = StartPos;
	}
}
