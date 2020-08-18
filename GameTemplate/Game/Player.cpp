#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"
#include "GameCamera.h"
#include "PlayerPad.h"


GamePlayer::GamePlayer()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Player.cmo");
	m_FrontModel.Init(L"Assets/modelData/player(front).cmo");
	m_BuckModel.Init(L"Assets/modelData/player(Back).cmo");
	m_Se.Init(L"Assets/sound/jump.wav");
	m_Se.SetVolume(0.2f);
	m_Se2.Init(L"Assets/sound/jump.wav");
	m_Se2.SetVolume(0.2f);
	m_Asioto.Init(L"Assets/sound/asioto.wav");
	m_Asioto.Play(true);
	m_Asioto.SetVolume(0.0f);
}


GamePlayer::~GamePlayer()
{
	SavePlayerData();
	DeleteGO(m_Magnet);
	DeleteGO(m_ThisNumSprite);
}

void GamePlayer::InitPad(PlayerPad* pad)
{
	m_Pad = pad;
}

void GamePlayer::ReSpown()
{
		m_position = m_CheckPoint;
		GameCamera* camera = FindGO<GameCamera>("camera");
		camera->SetDec(0.0f);
		m_IsSi = false;
		m_characon.Init(40.0f, 20.0f, m_position);
		LearnMO(m_Magnet);
		HaveMagnet = true;
		m_Magnet->SetPosition(&m_position);
		m_Scale.z = 1.0f;
	
}

void GamePlayer::SetCheckPoint(CVector3 spownPoint)
{
	m_CheckPoint = spownPoint;
}
bool GamePlayer::Start()
{
	m_ThisNumSprite = NewGO<SpriteRender>(0);
	wchar_t spriteName[256] = {};
	swprintf_s(spriteName, L"Assets/sprite/%dP_Pointer.dds", m_PlayerNum--);
	m_ThisNumSprite->Init(spriteName, 100.0f, 100.0f, true);
	CVector3 ThisNumSpritePos = m_position;
	ThisNumSpritePos.y += 150.0f;
	ThisNumSpritePos.x -= 50.0f;
	m_ThisNumSprite->SetPosition(ThisNumSpritePos);
	CQuaternion Rot;
	Rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_ThisNumSprite->SetRotation(Rot);
	//プレイヤーに磁力を持たせる
	m_Magnet = NewGO<Magnet>(1, "Magnet");
	LearnMO(m_Magnet); 
	HaveMagnet = true;
	m_Magnet->SetPosition(&m_position);
	m_Magnet->SetPad(&g_Pad[m_PlayerNum]);

	m_characon.Init(40.0f, 20.0f, m_position);
	m_AnimeClip[enAniCli::Run].Load(L"Assets/animData/PlayerRun.tka");
	m_AnimeClip[enAniCli::Run].SetLoopFlag(true);
	m_AnimeClip[enAniCli::Wait].Load(L"Assets/animData/wait.tka");
	m_AnimeClip[enAniCli::Wait].SetLoopFlag(true);
	m_AnimeClip[enAniCli::Junp].Load(L"Assets/animData/kirarajunp.tka");
	m_Animetion.Init(m_model, m_AnimeClip, enAniCli::AnimaitionNum);
	return true;
}

void GamePlayer::Update()
{
	//シャドウ関連の更新処理
	{

	}
	if (m_IsSi) {
		SIBOU();
	}
	else {
		if (g_Pad[m_PlayerNum].IsTrigger(enButtonLB2)) {
			m_position = m_CheckPoint;
			m_characon.SetPosition(m_CheckPoint);
			movespeed.y = 0.0f;
		}
		Move();
		MyMagnet();
		SpawnPole();
		m_Animetion.Update(1.0f / 60.0f);
	}
	{
		CVector3 ThisNumSpritePos = m_position;
		ThisNumSpritePos.y += 150.0f;
		float diff = fabsf(g_camera3D.GetTarget().x) - ThisNumSpritePos.x;
		ThisNumSpritePos.x -= (diff / 5.0f);
		m_ThisNumSprite->SetPosition(ThisNumSpritePos);
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rot, m_Scale);
	m_BuckModel.UpdateWorldMatrix(m_position, m_ReverseDefeatRot, m_Scale);
	m_FrontModel.UpdateWorldMatrix(m_position, m_DefeatRot, m_Scale);
}
void GamePlayer::Draw()
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


void GamePlayer::SpawnPole()
{
	CMatrix mrot = CMatrix::Identity();
	mrot.MakeRotationFromQuaternion(m_rot);
	m_forward = { mrot.m[2][0],mrot.m[2][1],mrot.m[2][2] };
	m_forward.Normalize();
	//NSpawn
	if (m_Pad->IsMagShotN())
	{
		QueryGOs<NPole>("npole", [&](NPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		NPole* npole = NewGO<NPole>(1, "npole");
		npole->SetPlayer(this);
		CVector3 SpawnDir = { g_Pad[m_PlayerNum].GetRStickXF() * -1.0f , g_Pad[m_PlayerNum].GetRStickYF() , 0.0f };
		if (SpawnDir.Length() < 0.01f) {
			SpawnDir = CVector3::Up();
		}
		npole->SetMoveDir(SpawnDir);
	}
	//SSpawn
	if (m_Pad->IsMagShotS())
	{
		QueryGOs< SPole>("spole", [&](SPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		SPole* spole = NewGO< SPole>(1, "spole");
		spole->SetPlayer(this);
		CVector3 MoveDir = { g_Pad[m_PlayerNum].GetRStickXF() * -1.0f , g_Pad[m_PlayerNum].GetRStickYF() , 0.0f };
		if (MoveDir.Length() < 0.01f) {
			MoveDir = CVector3::Up();
		}
		MoveDir.Normalize();
		spole->SetMoveDir(MoveDir);
	}
}

void GamePlayer::Move()
{
	//ジャンプ判定
	movespeed.x = 0.0f;
	movespeed.z = 0.0f;
	//左右の移動
	movespeed.x = m_Pad->MoveX() * -10.0f;
	const float junpPower = 15.0f;
	float Volume;
	if (m_characon.IsJump() &&
		g_Pad[m_PlayerNum].IsPress(enButtonA) &&
		JumpTimer < 1.0f) {
		movespeed.y = junpPower;
		JumpTimer += 0.5f;
	}
	if (m_characon.IsOnGround())
	{
		Volume = fabsf(m_Pad->MoveX());
		if (m_Pad->IsJump()) {
			movespeed.y = junpPower;
			if (m_Se.IsPlaying()) {
				m_Se2.Play(false);
			}
			m_Se.Play(false);
		}
		else {
			JumpTimer = 0.0f;
		}
	}
	const float gravity = 0.8f;		//重力
	movespeed.y -= gravity;
	Volume = fabsf(m_Pad->MoveX());
	if (movespeed.y >= 0.0f) {
		Volume -= 0.1f;
	}
	m_Asioto.SetVolume(Volume);

	if (fabsf(movespeed.x) > 0.0f
		&&m_characon.IsOnGround()
		) {
		m_Animetion.Play(enAniCli::Run, 0.3f);
	}
	else if (m_characon.IsOnGround()) {
		m_Animetion.Play(enAniCli::Wait, 0.3f);
	}
	if (movespeed.y > 0.0f) {
		m_Animetion.Play(enAniCli::Junp, 0.3f);
	}
	//磁石の移動
	movespeed += m_Magnet->MagnetMove();
	if (m_characon.IsOnGround() && movespeed.y < 0.0f) {
		movespeed.y = 0;
	}


	m_position = m_characon.Execute(1.0f, movespeed);
	if (m_Pad->MoveX() > 0.0f)
	{
		dir = Dir::L;
	}
	if (m_Pad->MoveX() < 0.0f)
	{
		dir = Dir::R;
	}
	if (dir == Dir::L) {
		m_rotAngle -= 45.0f;
		if (m_rotAngle < -90.0f) {
			m_rotAngle = -90.0f;
		}
	}
	if (dir == Dir::R) {
		m_rotAngle += 45.0f;
		if (m_rotAngle > 90.0f) {
			m_rotAngle = 90.0f;
		}
	}
	m_rot.SetRotationDeg(CVector3::AxisY(), m_rotAngle);
}

void GamePlayer::MyMagnet()
{
	if (m_Pad->IsMagN()) {
		m_Magnet->SetState(Magnet::State::NMode);
	}
	if (m_Pad->IsMagS()) {
		m_Magnet->SetState(Magnet::State::SMode);
	}
	if (m_Pad->IsNoMag()) {
		m_Magnet->SetState(Magnet::State::NoMode);
	}
}

void GamePlayer::SIBOU()				//OK
{
	m_characon.RemoveRigidBoby();
	if (HaveMagnet) {
		DeleteMO(m_Magnet);
		HaveMagnet = false;
	}
	//ここあとで修正
	if (m_Pad->IsNoMag()) {
		ReSpown();
	}
}

void GamePlayer::MagumaDead()				//OK
{
	m_position.y -= 1.0f;
	m_IsSi = true;

}

void GamePlayer::Cut()						//OK
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
	if (m_IsSi == false) {
		SoundSource m_bleeding;
		m_bleeding.Init(L"Assets/sound/bleeding.wav");
		m_bleeding.Play();
	}
	m_IsSi = true;
}

void GamePlayer::Press()					//OK
{
	if (m_IsSi == false) {
		SoundSource m_bleeding;
		m_bleeding.Init(L"Assets/sound/bleeding.wav");
		m_bleeding.Play();
	}
	m_IsSi = true;
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
	}
}