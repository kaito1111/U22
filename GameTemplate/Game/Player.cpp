#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"
#include "GameCamera.h"
#include "Network/NetworkLogic.h"

//コンストラクタ
GamePlayer::GamePlayer()
{
	m_model.Init(L"Assets/modelData/player.cmo");
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

//デストラクタ
GamePlayer::~GamePlayer()
{
	//SavePlayerData(this);
	if (HaveMagnet) {
		DeleteMO(m_Magnet); 
	}
	DeleteGO(m_Magnet);
	DeleteGO(m_ThisNumSprite);
}

//コントローラーを受け取る
void GamePlayer::SetPad(IPad* pad)
{
	//PlayerPad or NetworkPad の設定
	m_Pad = pad;
}



void GamePlayer::ReSpown()
{
	//プレイヤーをチェックポイントまで戻す
	m_position = m_CheckPoint;
	//カメラも
	GameCamera* camera = FindGO<GameCamera>("camera");
	camera->SetDec(0.0f);
	//死亡フラグを消す
	m_IsSi = false;
	//キャラコンをリセット
	m_characon.Init(40.0f, 20.0f, m_position);
	//磁極をリセット
	LearnMO(m_Magnet);
	//磁極を持ちました
	HaveMagnet = true;
	m_Magnet->SetPosition(&m_position);
	//プレス用
	m_Scale.z = 1.0f;
	//切断用
	m_PlayerCut = false;
}

bool GamePlayer::Start()
{
	//プレイヤーNoの絵を出す
	{
		m_ThisNumSprite = NewGO<SpriteRender>(0);
		wchar_t spriteName[256] = {};
		swprintf_s(spriteName, L"Assets/sprite/%dP_Pointer.dds", m_PlayerNum);
		m_ThisNumSprite->Init(spriteName, 100.0f, 100.0f, true);
		CVector3 ThisNumSpritePos = m_position;
		ThisNumSpritePos.y += 150.0f;
		ThisNumSpritePos.x -= 50.0f;
		m_ThisNumSprite->SetPosition(ThisNumSpritePos);
		CQuaternion Rot;
		Rot.SetRotationDeg(CVector3::AxisY(), 180.0f);
		m_ThisNumSprite->SetRotation(Rot);
	}
	//プレイヤーに磁力を持たせる
	m_Magnet = NewGO<Magnet>(1, "Magnet");
	LearnMO(m_Magnet); 
	HaveMagnet = true;
	m_Magnet->SetPosition(&m_position);
	m_Magnet->SetChange(false);
	//キャラコンをセット
	m_characon.Init(40.0f, 20.0f, m_position);

	//アニメーションをロード
	m_AnimeClip[enAniCli::Run].Load(L"Assets/animData/PlayerRun.tka");
	m_AnimeClip[enAniCli::Run].SetLoopFlag(true);
	m_AnimeClip[enAniCli::Wait].Load(L"Assets/animData/wait.tka");
	m_AnimeClip[enAniCli::Wait].SetLoopFlag(true);
	m_AnimeClip[enAniCli::Junp].Load(L"Assets/animData/kirarajunp.tka");
	m_Animetion.Init(m_model, m_AnimeClip, enAniCli::AnimaitionNum);

	//デバッグ用のスプライトを作成
	m_SpriteBase = NewGO<SpriteRender>(3);
	m_SpriteBase->Init(L"Assets/sprite/PadBase.dds", 250.0f, 250.0f);
	m_SpriteBase->SetPosition({ 500.0f,-250.0f,0.0f });
	m_SpriteDel = NewGO<SpriteRender>(4);
	m_SpriteDel->Init(L"Assets/sprite/del.dds", 500.0f,500.0f);
	m_SpriteDel->SetPosition({ 550.0f,-250,0.0f });
	m_SpriteDel->SetW(0.0f);
	m_SpriteJump = NewGO<SpriteRender>(4);
	m_SpriteJump->Init(L"Assets/sprite/jump.dds", 500.0f,500.0f);
	m_SpriteJump->SetPosition({ 500.0f,-300.0f,0.0 });
	m_SpriteJump->SetW(0.0f);
	m_SpriteN = NewGO<SpriteRender>(4);
	m_SpriteN->Init(L"Assets/sprite/N.dds", 500.0f, 500.0f);
	m_SpriteN->SetPosition({ 450.0f,-250.0f,0.0 });
	m_SpriteN->SetW(0.0f);
	m_SpriteS = NewGO<SpriteRender>(4);
	m_SpriteS->Init(L"Assets/sprite/S.dds", 500.0f, 500.0f);
	m_SpriteS->SetPosition({ 500.0f,-200.0f,0.0f });
	m_SpriteS->SetW(0.0f);
	return true;
}

void GamePlayer::Update()
{
	//あぷでーどlog
	times++;
	//printf("player %d Updated\n", m_PlayerNum);
	m_SpriteJump->SetW(0.0f);
	m_SpriteDel->SetW(0.0f);
	m_SpriteN->SetW(0.0f);
	m_SpriteS->SetW(0.0f);
	//しんだ?
	if (m_IsSi) {
		SIBOU();
	}
	else {
		//デバッグ用簡易リスポーン
		if (g_Pad[GetPadNo()].IsTrigger(enButtonLB2)) {
			StartPos();
		}
		//移動
		Move();
		//磁力変更
		MyMagnet();
		//磁極を作成
		SpawnPole();
		//アニメーションをアップデート
		m_Animetion.Update(1.0f / 60.0f);
	}
	{
		//何Pの絵を動かす
		CVector3 ThisNumSpritePos = m_position;
		ThisNumSpritePos.y += 150.0f;
		float diff = fabsf(g_camera3D.GetTarget().x) - ThisNumSpritePos.x;
		ThisNumSpritePos.x -= (diff / 5.0f);
		m_ThisNumSprite->SetPosition(ThisNumSpritePos);
	}
	//ワールド行列の更新。
	if (INetworkLogic().GetLBL()->GetPlayerNum() == 1) {
		if (GetPadNo() == 0) {
			//player1
			//ポジション確認
			printf("player %d 's position is %f frameNo is %d\n", INetworkLogic().GetLBL()->GetPlayerNum(), m_position.x, times);
			//パッドの入力量(送信)
			//printf("playerPadState Sent. value is %f\n", g_Pad[GetPadNo()].GetLStickXF());
			//Aボタン入力(送信）
			//if (g_Pad[GetPadNo()].IsTrigger(enButtonA)) {
			//	printf("Sent AButton Presed. %d times.\n", times);
			//}
			//Update確認
			//printf("p1 Updated. %d.\n", times);
		}
		else
		{
			//net(p2)
			printf("player %d 's position is %f frameNo is %d\n", INetworkLogic().GetLBL()->GetPlayerNum() + 1, m_position.x, times);
			//printf("p2 Updated. %d.\n", times);
		}

	}
	else {
		if (GetPadNo() == 0) {
			//player2
			printf("player %d 's position is %f frameNo is %d\n", INetworkLogic().GetLBL()->GetPlayerNum(), m_position.x, times);
			//printf("p2 Updated. %d.\n", times);
		}
		else
		{
			//net(p1)
			printf("player %d 's position is %f frameNo is %d\n", INetworkLogic().GetLBL()->GetPlayerNum() - 1, m_position.x, times);
			//パッドの入力量(受け取り)
			//printf("playerPadState Receved. value is %f\n", g_Pad[GetPadNo()].GetLStickXF());
			//Aボタン入力(受け取り)
			//if (g_Pad[GetPadNo()].IsTrigger(enButtonA)) {
			//	printf("Receved AButton Presed. %d times.\n", times);
			//}
			//printf("p1 Updated. %d.\n", times);
		}
	}

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

void GamePlayer::StartPos()
{
	m_position = m_CheckPoint;
	m_characon.SetPosition(m_CheckPoint);
	movespeed.y = 0.0f;
}

int GamePlayer::GetPadNo() const
{
	if (INetworkLogic().GetLBL()->GetPlayerNum() == m_PlayerNum) {
		//自分が操作しているPadだった
		return 0;
	}
	else {
		//操作していないほうのPad
		return 1;
	}
}
void GamePlayer::SpawnPole()
{
	//NSpawn
	if (g_Pad[GetPadNo()].IsTrigger(enButtonRB1))
	{
		//Game上のN極をすべて消す
		QueryGOs<NPole>("npole", [&](NPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		//N極を出す
		NPole* npole = NewGO<NPole>(1, "npole");
		//出る位置を伝える
		npole->SetSpownPos(m_position);
		//方向を設定
		CVector3 SpawnDir = { g_Pad[GetPadNo()].GetRStickXF() * -1.0f , g_Pad[GetPadNo()].GetRStickYF() , 0.0f };
		if (SpawnDir.Length() < 0.01f) {
			SpawnDir = CVector3::Up();
		}
		//方向を正規化
		SpawnDir.Normalize();
		//方向をセット
		npole->SetMoveDir(SpawnDir);
	}
	//SSpawn
	if (g_Pad[GetPadNo()].IsTrigger(enButtonLB1))
	{
		//Game上のS極をすべて消す
		QueryGOs< SPole>("spole", [&](SPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		//S極を出す
		SPole* spole = NewGO< SPole>(1, "spole");
		//出る位置を伝える
		spole->SetSpownPos(m_position);
		//方向を設定
		CVector3 MoveDir = { g_Pad[GetPadNo()].GetRStickXF() * -1.0f , g_Pad[GetPadNo()].GetRStickYF() , 0.0f };
		if (MoveDir.Length() < 0.01f) {
			MoveDir = CVector3::Up();
		}
		//方向を正規化
		MoveDir.Normalize();
		//方向をセット
		spole->SetMoveDir(MoveDir);
	}
}

void GamePlayer::Move()
{
	movespeed.x = 0.0f;
	movespeed.z = 0.0f;
	//左右の移動
	movespeed.x = g_Pad[GetPadNo()].GetLStickXF()* -10.0f;
	const float junpPower = 15.0f;
	//ジャンプ判定
	if (m_characon.IsOnGround())
	{
		if (g_Pad[GetPadNo()].IsTrigger(enButtonA)) {
			m_SpriteJump->SetW(1.0f);
			movespeed.y = junpPower;
			if (m_Se.IsPlaying()) {
				m_Se2.Play(false);
			}
			m_Se.Play(false);
		}
	}
	{
		const float gravity = 0.8f;		//重力
		movespeed.y -= gravity;
	}
	{
		//音の設定
		float Volume = fabsf(g_Pad[GetPadNo()].GetLStickXF());
		//右スティック量を書き出す
		if (GetPadNo() == 1) {
			//printf("プレイヤーパッドLスティックX %f\n", g_Pad[GetPadNo()].GetLStickXF());
		}
		else {
			//printf("ネットワークパッドLスティックX %f\n", g_Pad[GetPadNo()].GetLStickXF());
		}

		if (movespeed.y >= 0.0f) {
			Volume -= 0.1f;
		}
		m_Asioto.SetVolume(Volume);
	}
	//どのアニメーションを流すか指定する

	if (fabsf(movespeed.x) > 0.0f//横に動いていて
		&&m_characon.IsOnGround()//飛んでないなら
		) {
		//走る
		m_Animetion.Play(enAniCli::Run, 0.3f);
	}
	else if (m_characon.IsOnGround()//突っ立ってるだけなら
		) {
		//棒立ち
		m_Animetion.Play(enAniCli::Wait, 0.3f);
	}
	if (movespeed.y > 0.0f//上に飛んでるなら
		) {
		//飛ぶ
		m_Animetion.Play(enAniCli::Junp, 0.3f);
	}
	//磁石の移動
	movespeed += m_Magnet->MagnetMove();

	//地面についているのに下へ向かうのはおかしいので
	//ｙ方向は０に
	if (m_characon.IsOnGround() && movespeed.y < 0.0f) {
		movespeed.y = 0;
	}
	movespeed.z = 0.0f;
	//移動を確定
	m_position = m_characon.Execute(1.0f, movespeed);

	//左にスティックが傾いた
	if (g_Pad[GetPadNo()].GetLStickXF() > 0.0f)
	{
		dir = Dir::L;
	}
	//右にスティックが傾いた
	if (g_Pad[GetPadNo()].GetLStickXF() < 0.0f)
	{
		dir = Dir::R;
	}
	//回転量を制限
	{
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
	}
	//回転をセット
	m_rot.SetRotationDeg(CVector3::AxisY(), m_rotAngle);
}

//磁極を変更できる
void GamePlayer::MyMagnet()
{
	if (g_Pad[GetPadNo()].IsPress(enButtonX)) {
		m_SpriteN->SetW(1.0f);
		m_Magnet->SetState(Magnet::State::NMode);
	}
	if (g_Pad[GetPadNo()].IsPress(enButtonY)) {
		m_SpriteS->SetW(1.0f);
		m_Magnet->SetState(Magnet::State::SMode);
	}
	if (g_Pad[GetPadNo()].IsPress(enButtonB)) {
		m_SpriteDel->SetW(1.0f);
		m_Magnet->SetState(Magnet::State::NoMode);
	}
}

void GamePlayer::SIBOU()
{
	//当たり判定を一度放棄
	m_characon.RemoveRigidBoby();
	//磁力も無くす
	if (HaveMagnet) {
		DeleteMO(m_Magnet);
		HaveMagnet = false;
	}
	//修正しました
	if (g_Pad[GetPadNo()].IsPress(enButtonA)) {
		ReSpown();
	}
}

//沈んで死ぬ
void GamePlayer::MagumaDead()
{
	m_position.y -= 1.0f;
	m_IsSi = true;

}

//切断処理
void GamePlayer::Cut()
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

//圧殺
void GamePlayer::Press()
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