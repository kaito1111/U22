#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"
#include "GameCamera.h"

Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_Magnet);
}

bool Player::Start()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Player.cmo");
	m_characon.Init(20.0f, 50.0f, m_position);
	//プレイヤーに磁力を持たせる
	m_Magnet = NewGO<Magnet>(1, "Magnet");
	LearnMO(m_Magnet, &m_position);
	m_FrontModel.Init(L"Assets/modelData/player(front).cmo");
	m_BuckModel.Init(L"Assets/modelData/player(Back).cmo");
	return true;
}

void Player::Update()
{
	MyMagnet();
	SpawnPole();
	if (m_Pad->IsTrigger(enButtonX)) {
		SIBOU();
	}
	if (m_IsSi) {
		SIBOU();
	}
	else {
		Move();
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rot, m_Scale);
	m_BuckModel.UpdateWorldMatrix(m_position, m_ReverseDefeatRot, m_Scale);
	m_FrontModel.UpdateWorldMatrix(m_position, m_DefeatRot, m_Scale);
}
void Player::Draw()
{
	if (!m_PlayerCut) {
		//シルエット用の描画
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			1
		);
		//シルエットなし用の描画
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			0
		);
	}
	if (m_PlayerCut) {
		m_FrontModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			1
		);
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			0
		);
	}
	if (m_PlayerCut) {
		m_BuckModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			1
		);
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			0
		);
	}
}

void Player::SpawnPole()
{
	CMatrix mrot = CMatrix::Identity();
	mrot.MakeRotationFromQuaternion(m_rot);
	m_forward = { mrot.m[2][0],mrot.m[2][1],mrot.m[2][2] };
	m_forward.Normalize();
	//NSpawn
	if (m_Pad->IsTrigger(enButtonRB1))
	{
		QueryGOs<NPole>("npole", [&](NPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		NPole* npole = NewGO<NPole>(1, "npole");
		npole->SetPlayer(this);
		CVector3 SpawnDir = { m_Pad->GetRStickXF() * -1.0f , m_Pad->GetRStickYF() , 0.0f };
		if (SpawnDir.Length() < 0.01f) {
			SpawnDir = CVector3::Up();
		}
		npole->SetMoveDir(SpawnDir);
	}
	//SSpawn
	if (m_Pad->IsTrigger(enButtonLB1))
	{
		QueryGOs< SPole>("spole", [&](SPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		SPole* spole = NewGO< SPole>(1, "spole");
		spole->SetPlayer(this);
		CVector3 MoveDir = { m_Pad->GetRStickXF() * -1.0f , m_Pad->GetRStickYF() , 0.0f };
		if (MoveDir.Length() < 0.01f) {
			MoveDir = CVector3::Up();
		}
		MoveDir.Normalize();
		spole->SetMoveDir(MoveDir);
	}
}

void Player::Move()
{
	//ジャンプ判定
	CVector3 movespeed = CVector3::Zero();
	const float junpPower = 60.0f;
	if (m_characon.IsJump() &&
		m_Pad->IsPress(enButtonB)&&
		JumpTimer < 1.0f) {
		movespeed.y = junpPower;
		JumpTimer += 0.5f;
	}
	if (m_characon.IsOnGround())
	{
		if (m_Pad->IsTrigger(enButtonB)) {
			movespeed.y = junpPower;
		}
		else {
			JumpTimer = 0.0f;
		}
	}

	const float gravity = 5.0f;		//重力
	movespeed.y -= gravity;

	//左右の移動
	movespeed.x = m_Pad->GetLStickXF() * -20.0f;

	//磁石の移動
	movespeed += m_Magnet->MagnetMove();
	if (m_characon.IsOnGround()&&movespeed.y<0.0f) {
		movespeed.y = 0;
	}


	m_position = m_characon.Execute(1.0f, movespeed);
	if (m_Pad->GetLStickXF() > 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), -90.0f);
	}
	if (m_Pad->GetLStickXF() < 0.0f)
	{
		m_rot.SetRotationDeg(CVector3::AxisY(), 90.0f);
	}
}

void Player::MyMagnet()
{
	if (m_Pad->IsTrigger(enButtonX)) {
		if (m_Magnet->GetState() == Magnet::State::NMode) {
			m_Magnet->SetState(Magnet::State::NoMode);
		}
		else {
			m_Magnet->SetState(Magnet::State::NMode);
		}
	}
	if (m_Pad->IsTrigger(enButtonY)) {
		if (m_Magnet->GetState() == Magnet::State::SMode) {
			m_Magnet->SetState(Magnet::State::NoMode);
		}
		else {
			m_Magnet->SetState(Magnet::State::SMode);
		}
	}
}

void Player::SIBOU()				//OK
{
	if (m_Pad->IsTrigger(enButtonA)) {
		m_position = CVector3::Zero();
		GameCamera* camera = FindGO<GameCamera>("camera");
		camera->SetDec(0.0f);
		m_IsSi = false;
	}
}

void Player::MagumaDead()				//OK
{
	m_position.y -= 1.0f;
	m_IsSi = true;

}

void Player::Cut()						//OK
{
	m_PlayerCut = true;
	rate += 2.0f;
	if (rate > 90.0f) {
		rate = 90.0f;
	}
	m_DefeatRot.SetRotationDeg(CVector3::AxisZ(), rate);
	m_DefeatRot.Multiply(m_rot);
	m_ReverseDefeatRot.SetRotationDeg(CVector3::AxisZ(), -rate);
	m_ReverseDefeatRot.Multiply(m_rot);
	Effect* effect = NewGO<Effect>(1);
	if (!effect->IsPlay()) {
		effect->Play(L"Assets/effect/hemohage.efk");
		effect->SetPosition(m_position);
		effect->SetScale(CVector3::One() * 20);
	}
	m_IsSi = true;
}

void Player::Press()					//OK
{
	if (m_Scale.z >= 1.0f) {
		Effect* effect = NewGO<Effect>(1);
		if (!effect->IsPlay()) {
			effect->Play(L"Assets/effect/ti.efk");
			effect->SetPosition(m_position);
			effect->SetScale(CVector3::One() * 20);
		}
	}
	m_Scale.z -= 0.1f;
	if (m_Scale.z <= 0.1f) {
		m_Scale.z = 0.1f;
		m_IsSi = true;
	}
	if (m_Pad->IsTrigger(enButtonA)) {
		m_Scale.z = 1.0f;
	}
}