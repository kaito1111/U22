#include "stdafx.h"
#include "moveFloor.h"
#include "Player.h"
#include"HID/Pad.h"
//moveFloor::moveFloor(const wchar_t * modelName, CVector3 pos, CQuaternion rot)
//{
//	m_model.Init(modelName);
//	m_pos = pos;
//	m_rot = rot;
//}
moveFloor::moveFloor()
{
	
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

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/moveFloor.cmo");
	m_pos = { 0.0f,100.0f,0.0f };
	//m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);//静的物理オブジェクト
	int MaxPlayer = Pad::CONNECT_PAD_MAX;
	/*for (int PadNum = 1; PadNum < MaxPlayer ; PadNum++) {
		char pl[256];
		sprintf(pl, "player%d", PadNum+1);

		player[PadNum] = FindGO<Player>(pl);
	}*/
	
	return true;
}

void moveFloor::Update()
{
	//メッシュの云々。要するに当たり判定
	Move();

	m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);//静的物理オブジェクト
	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void moveFloor::Move()
{
	const float speedUPLimit = 10;  //スピードの上限
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

void moveFloor::SetDotUpdate()
{

	////動く床のサイズ

	//const float LengthAndWidth = 100.0f;//縦と横の長さ
	//const float height =		 20.0f;//高さ
	//const float side =			 200.0f;//横の長さ

	/////////前////////////
	////右上
	//FrontRightUp.x += side;
	//FrontRightUp.y += height;

	////右下
	//FrontRightDown.x += side;

	////左上
	//FrontLeftUp.x -= side;
	//FrontLeftUp.y += height;

	////左下
	//FrontLeftDown.x -= side;


	////プレイヤーの当たり判定のサイズ.10,100
	//const float PlayerYSize = 100.0f;
	//const float PlayerXSize = 10.0f;

	//if (PlayerNum >= 5) {
	//	PlayerNum = 1;
	//}
	//CVector3 PlayerPos = player[PlayerNum]->GetPosition();
	//PlayerRightUp = PlayerPos;
	//PlayerRightDown = PlayerPos;
	//PlayerLeftUp = PlayerPos;
	//PlayerLeftDown = PlayerPos;


	////プレイヤーの右上
	//PlayerRightUp.x += PlayerXSize;
	//PlayerRightUp.y += PlayerYSize;

	////プレイヤーの右下
	//PlayerRightDown.x += PlayerXSize;

	////プレイヤーの左上
	//PlayerLeftUp.x -= PlayerXSize;
	//PlayerLeftUp.y += PlayerYSize;

	////プレイヤーの左下
	//PlayerLeftDown.x -= PlayerXSize;


	//PlayerNum++;
}

void moveFloor::CollisionDetection()
{
	
}
