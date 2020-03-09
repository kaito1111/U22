#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ -300.0f, 100.0f, 1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	for (int i = 0; i < m_PlayerNum + 1; i++) {
		char PlayerNo[256] = {};
		sprintf(PlayerNo, "player%d", m_PlayerNum + 1);
		QueryGOs<Player>(PlayerNo, [&](Player* player)->bool {
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

	//PlayerNumが0だからこれ入ってない
	for (int i = 0; i < m_PlayerNum; i++) {
	Target += m_Player[i]->GetPosition();
	Target.y += 100.0f;

	}
	//上でカメラの位置が調整されてないので無理やり調整
	//上直したら消してね
	//Target.y += 100.0f;

	//プレイヤーが2人以上いるから真ん中をとる
	Target /= m_PlayerNum;

	//下の限界を更新
	/*if (Decline < Target.y) {
		Decline = Target.y;
	}
	else {
		Target.y = Decline;
	}*/

	//プレイヤーを殺す
	if (m_Player[0]->GetPosition().y < Target.y - 200.0f) {
		m_Player[0]->SIBOU();
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
	CVector3 pos = Target;
	pos.z += 500.0f;
	g_camera3D.SetTarget(Target); 
	g_camera3D.SetPosition(pos);
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
