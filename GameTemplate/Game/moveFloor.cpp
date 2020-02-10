#include "stdafx.h"
#include "moveFloor.h"


//moveFloor::moveFloor(const wchar_t * modelName, CVector3 pos, CQuaternion rot)
//{
//	m_model.Init(modelName);
//	m_pos = pos;
//	m_rot = rot;
//}
moveFloor::moveFloor()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/moveFloor.cmo");
	m_pos = {50.0f,50.0f,0.0f};
	m_phyStaticObject.CreateMeshObject(m_model, m_pos, m_rot);
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

void moveFloor::Update()
{
	//メッシュの云々。要するに当たり判定
	

	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void moveFloor::Move()
{
	


	const float speedLimit = 100;//スピードの上限

	//初期位置は上。下がるプログラム。
	if (UDPos == false && sLimit == false) {
		m_pos.y += -moveSpeed;	  //動くスピードが上がる
		moveSpeed++;
		if (moveSpeed >= speedLimit) {
			sLimit = true;		  //スピードが上限まで来たから変える
		}
	}
	if (UDPos == false&& sLimit == true) {//一定値までスピードが上がると
		moveSpeed--;              //スピードを下げていく。
		if (moveSpeed <= 0)		  //スピードが０以下になったら
			moveSpeed = 0;        //スピードに０を入れる。
			UDPos = true;		  //下がるモードから上がるモードへ。
			sLimit = false;		  //スピードリミットを戻す。
	}

	//上がるプログラム
	if (UDPos == true && sLimit == false) {
		m_pos.y += moveSpeed;			  //動くスピードが上がる
		moveSpeed++;
		if (moveSpeed >= speedLimit) {
			sLimit = true;				  //速度を下げる状態に切り替えるフラグ
		}
	}
	if (UDPos == true && sLimit == true) {//一定値までスピードが上がると
		moveSpeed--;                      //スピードを下げていく。
		if (moveSpeed <= 0)				  //スピードが０以下になったら
			moveSpeed = 0;				  //スピードに０を入れる。
		UDPos = true;					  //上がるモードから下がるモードへ。
		sLimit = false;					  //速度を戻す。
	}


	
}
