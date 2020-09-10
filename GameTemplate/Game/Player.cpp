#include "stdafx.h"
#include "Player.h"
#include "NPole.h"
#include "SPole.h"
#include "GameCamera.h"
#include "Network/NetworkLogic.h"

//�R���X�g���N�^
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

//�f�X�g���N�^
GamePlayer::~GamePlayer()
{
	//SavePlayerData(this);
	if (HaveMagnet) {
		DeleteMO(m_Magnet); 
	}
	DeleteGO(m_Magnet);
	DeleteGO(m_ThisNumSprite);
}

//�R���g���[���[���󂯎��
void GamePlayer::SetPad(IPad* pad)
{
	//PlayerPad or NetworkPad �̐ݒ�
	m_Pad = pad;
}



void GamePlayer::ReSpown()
{
	//�v���C���[���`�F�b�N�|�C���g�܂Ŗ߂�
	m_position = m_CheckPoint;
	//�J������
	GameCamera* camera = FindGO<GameCamera>("camera");
	camera->SetDec(0.0f);
	//���S�t���O������
	m_IsSi = false;
	//�L�����R�������Z�b�g
	m_characon.Init(40.0f, 20.0f, m_position);
	//���ɂ����Z�b�g
	LearnMO(m_Magnet);
	//���ɂ������܂���
	HaveMagnet = true;
	m_Magnet->SetPosition(&m_position);
	//�v���X�p
	m_Scale.z = 1.0f;
	//�ؒf�p
	m_PlayerCut = false;
}

bool GamePlayer::Start()
{
	//�v���C���[No�̊G���o��
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
	//�v���C���[�Ɏ��͂���������
	m_Magnet = NewGO<Magnet>(1, "Magnet");
	LearnMO(m_Magnet); 
	HaveMagnet = true;
	m_Magnet->SetPosition(&m_position);
	m_Magnet->SetChange(false);
	//�L�����R�����Z�b�g
	m_characon.Init(40.0f, 20.0f, m_position);

	//�A�j���[�V���������[�h
	m_AnimeClip[enAniCli::Run].Load(L"Assets/animData/PlayerRun.tka");
	m_AnimeClip[enAniCli::Run].SetLoopFlag(true);
	m_AnimeClip[enAniCli::Wait].Load(L"Assets/animData/wait.tka");
	m_AnimeClip[enAniCli::Wait].SetLoopFlag(true);
	m_AnimeClip[enAniCli::Junp].Load(L"Assets/animData/kirarajunp.tka");
	m_Animetion.Init(m_model, m_AnimeClip, enAniCli::AnimaitionNum);

	//�f�o�b�O�p�̃X�v���C�g���쐬
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
	//���ՂŁ[��log
	times++;
	//printf("player %d Updated\n", m_PlayerNum);
	m_SpriteJump->SetW(0.0f);
	m_SpriteDel->SetW(0.0f);
	m_SpriteN->SetW(0.0f);
	m_SpriteS->SetW(0.0f);
	//����?
	if (m_IsSi) {
		SIBOU();
	}
	else {
		//�f�o�b�O�p�ȈՃ��X�|�[��
		if (g_Pad[GetPadNo()].IsTrigger(enButtonLB2)) {
			StartPos();
		}
		//�ړ�
		Move();
		//���͕ύX
		MyMagnet();
		//���ɂ��쐬
		SpawnPole();
		//�A�j���[�V�������A�b�v�f�[�g
		m_Animetion.Update(1.0f / 60.0f);
	}
	{
		//��P�̊G�𓮂���
		CVector3 ThisNumSpritePos = m_position;
		ThisNumSpritePos.y += 150.0f;
		float diff = fabsf(g_camera3D.GetTarget().x) - ThisNumSpritePos.x;
		ThisNumSpritePos.x -= (diff / 5.0f);
		m_ThisNumSprite->SetPosition(ThisNumSpritePos);
	}
	//���[���h�s��̍X�V�B
	if (INetworkLogic().GetLBL()->GetPlayerNum() == 1) {
		if (GetPadNo() == 0) {
			//player1
			//�|�W�V�����m�F
			printf("player %d 's position is %f frameNo is %d\n", INetworkLogic().GetLBL()->GetPlayerNum(), m_position.x, times);
			//�p�b�h�̓��͗�(���M)
			//printf("playerPadState Sent. value is %f\n", g_Pad[GetPadNo()].GetLStickXF());
			//A�{�^������(���M�j
			//if (g_Pad[GetPadNo()].IsTrigger(enButtonA)) {
			//	printf("Sent AButton Presed. %d times.\n", times);
			//}
			//Update�m�F
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
			//�p�b�h�̓��͗�(�󂯎��)
			//printf("playerPadState Receved. value is %f\n", g_Pad[GetPadNo()].GetLStickXF());
			//A�{�^������(�󂯎��)
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
		//�V���G�b�g�p�̕`��
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			1
		);
		//�V���G�b�g�Ȃ��p�̕`��
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
		//���������삵�Ă���Pad������
		return 0;
	}
	else {
		//���삵�Ă��Ȃ��ق���Pad
		return 1;
	}
}
void GamePlayer::SpawnPole()
{
	//NSpawn
	if (g_Pad[GetPadNo()].IsTrigger(enButtonRB1))
	{
		//Game���N�ɂ����ׂď���
		QueryGOs<NPole>("npole", [&](NPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		//N�ɂ��o��
		NPole* npole = NewGO<NPole>(1, "npole");
		//�o��ʒu��`����
		npole->SetSpownPos(m_position);
		//������ݒ�
		CVector3 SpawnDir = { g_Pad[GetPadNo()].GetRStickXF() * -1.0f , g_Pad[GetPadNo()].GetRStickYF() , 0.0f };
		if (SpawnDir.Length() < 0.01f) {
			SpawnDir = CVector3::Up();
		}
		//�����𐳋K��
		SpawnDir.Normalize();
		//�������Z�b�g
		npole->SetMoveDir(SpawnDir);
	}
	//SSpawn
	if (g_Pad[GetPadNo()].IsTrigger(enButtonLB1))
	{
		//Game���S�ɂ����ׂď���
		QueryGOs< SPole>("spole", [&](SPole* m_pole)->bool {
			DeleteGO(m_pole);
			return true;
		});
		//S�ɂ��o��
		SPole* spole = NewGO< SPole>(1, "spole");
		//�o��ʒu��`����
		spole->SetSpownPos(m_position);
		//������ݒ�
		CVector3 MoveDir = { g_Pad[GetPadNo()].GetRStickXF() * -1.0f , g_Pad[GetPadNo()].GetRStickYF() , 0.0f };
		if (MoveDir.Length() < 0.01f) {
			MoveDir = CVector3::Up();
		}
		//�����𐳋K��
		MoveDir.Normalize();
		//�������Z�b�g
		spole->SetMoveDir(MoveDir);
	}
}

void GamePlayer::Move()
{
	movespeed.x = 0.0f;
	movespeed.z = 0.0f;
	//���E�̈ړ�
	movespeed.x = g_Pad[GetPadNo()].GetLStickXF()* -10.0f;
	const float junpPower = 15.0f;
	//�W�����v����
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
		const float gravity = 0.8f;		//�d��
		movespeed.y -= gravity;
	}
	{
		//���̐ݒ�
		float Volume = fabsf(g_Pad[GetPadNo()].GetLStickXF());
		//�E�X�e�B�b�N�ʂ������o��
		if (GetPadNo() == 1) {
			//printf("�v���C���[�p�b�hL�X�e�B�b�NX %f\n", g_Pad[GetPadNo()].GetLStickXF());
		}
		else {
			//printf("�l�b�g���[�N�p�b�hL�X�e�B�b�NX %f\n", g_Pad[GetPadNo()].GetLStickXF());
		}

		if (movespeed.y >= 0.0f) {
			Volume -= 0.1f;
		}
		m_Asioto.SetVolume(Volume);
	}
	//�ǂ̃A�j���[�V�����𗬂����w�肷��

	if (fabsf(movespeed.x) > 0.0f//���ɓ����Ă���
		&&m_characon.IsOnGround()//���łȂ��Ȃ�
		) {
		//����
		m_Animetion.Play(enAniCli::Run, 0.3f);
	}
	else if (m_characon.IsOnGround()//�˂������Ă邾���Ȃ�
		) {
		//�_����
		m_Animetion.Play(enAniCli::Wait, 0.3f);
	}
	if (movespeed.y > 0.0f//��ɔ��ł�Ȃ�
		) {
		//���
		m_Animetion.Play(enAniCli::Junp, 0.3f);
	}
	//���΂̈ړ�
	movespeed += m_Magnet->MagnetMove();

	//�n�ʂɂ��Ă���̂ɉ��֌������̂͂��������̂�
	//�������͂O��
	if (m_characon.IsOnGround() && movespeed.y < 0.0f) {
		movespeed.y = 0;
	}
	movespeed.z = 0.0f;
	//�ړ����m��
	m_position = m_characon.Execute(1.0f, movespeed);

	//���ɃX�e�B�b�N���X����
	if (g_Pad[GetPadNo()].GetLStickXF() > 0.0f)
	{
		dir = Dir::L;
	}
	//�E�ɃX�e�B�b�N���X����
	if (g_Pad[GetPadNo()].GetLStickXF() < 0.0f)
	{
		dir = Dir::R;
	}
	//��]�ʂ𐧌�
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
	//��]���Z�b�g
	m_rot.SetRotationDeg(CVector3::AxisY(), m_rotAngle);
}

//���ɂ�ύX�ł���
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
	//�����蔻�����x����
	m_characon.RemoveRigidBoby();
	//���͂�������
	if (HaveMagnet) {
		DeleteMO(m_Magnet);
		HaveMagnet = false;
	}
	//�C�����܂���
	if (g_Pad[GetPadNo()].IsPress(enButtonA)) {
		ReSpown();
	}
}

//����Ŏ���
void GamePlayer::MagumaDead()
{
	m_position.y -= 1.0f;
	m_IsSi = true;

}

//�ؒf����
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

//���E
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