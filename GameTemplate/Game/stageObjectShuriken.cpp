#include "stdafx.h"
#include "stageObjectShuriken.h"

//動作確認とかするためのコンストラクタ。最終消す。
stageObjectShuriken::stageObjectShuriken()
{
	
}

//レベル配置用のコンストラクタ
//stageObjectShuriken::stageObjectShuriken(const wchar_t * modelName, CVector3 pos, CQuaternion rot)
//{
//}

stageObjectShuriken::~stageObjectShuriken()
{
}

bool stageObjectShuriken::Start()
{
	//モデルどうしようか。
	m_model.Init(L"Assets/modelData/shuriken.cmo");

	return true;
}

void stageObjectShuriken::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void stageObjectShuriken::Update()
{
	//ここに書いてあるのどっかで見たことあるとか言ってはいけない。
	const float speedUPLimit = 10;  //スピードの上限
	const float speedDownLimit = 0;//スピードの下限
	const float speed = 0.1;

	//migi
	if (UDPos == false) {

		//hidari
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
				UDPos = true;					//下がり切っているので左右フラグも切り替える
				moveSpeed = speedDownLimit;		//スピードを0に合わせる
			}
		}
		m_pos.x += moveSpeed;
	}

	//migi
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
		m_pos.x -= moveSpeed;
	}
}