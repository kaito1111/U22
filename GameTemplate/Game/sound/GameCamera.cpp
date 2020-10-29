#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_CharaCon.Init(30.0f, 30.0f, m_Pos);
	for (int i = 0; i < m_PlayerNum + 1; i++) {
		char PlayerNo[256] = {}; 
		sprintf(PlayerNo, "player%d", m_PlayerNum + 1);
		QueryGOs<GamePlayer>(PlayerNo, [&](GamePlayer* player)->bool {
			m_Player[m_PlayerNum] = player;
			m_PlayerNum++;
			return true;
		});
	}

	return true;
}

void GameCamera::Update()
{
	CVector3 Target = CVector3::Zero();

	for (int i = 0; i < m_PlayerNum; i++) {
		CVector3 m_PlPos = m_Player[i]->GetPosition();


		Target += m_PlPos;
	}
	//上でカメラの位置が調整されてないので無理やり調整
	//上直したら消してね
	//Target.y += 100.0f;

	//プレイヤーが2人以上いるから真ん中をとる
	Target /= m_PlayerNum;
	Target.y += 100.0f;

	//下の限界を更新
	/*if (Decline < Target.y) {
		Decline = Target.y;
	}
	else {
		Target.y = Decline;
	}*/

	//プレイヤーを殺す
	for (int i = 0; i < m_PlayerNum; i++) {
		if (m_Player[i]->GetPosition().y < Target.y - 500.0f) {
			m_Player[i]->SetIsSi();
		}
	}

	if (Target.x > 300.0f) {
		Target.x = 300.0f;
	}
	if (Target.x < 200.0f) {
		Target.x = 200.0f;
	}
	if (Target.y < 190.0f) {
		Target.y = 190.0f;
	}
	m_Pos = Target;
	m_Pos.z = 500.0f;
	//CVector3 move = m_Pos - NextPosition;
	//if (move.Length() > 0.01f) {
	//	m_Pos = m_CharaCon.Execute(1.0f, move);
	//}
	//else {
	//	m_Pos = move;
	//}
	//m_Pos.z += 500.0f;
	//m_Pos = NextPosition;
	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(m_Pos);
	//カメラの更新。
	g_camera3D.Update();    

	//デバッグ用のカメラ
	{
		////注視点から視点に向かって伸びるベクトルを計算する。
		//CVector3 toPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
		////カメラを回すクォータニオンを作成する。
		//CQuaternion qAddRot;
		////ゲームパッドの左スティックでカメラが回る。
		////ゲームパッドがない人はキーボードの'a'と'd'で回せるよ。
		//qAddRot.SetRotation(CVector3::AxisY(), 0.01f);
		////注視点から視点に向かって伸びるベクトルを回す。
		//qAddRot.Multiply(toPos);
		////新しい視点を計算する。
		//g_camera3D.SetPosition(g_camera3D.GetTarget() + toPos);
		//g_camera3D.Update();
	}
}
