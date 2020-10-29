#include "stdafx.h"
#include "TitlePlayer.h"

TitlePlayer::TitlePlayer()
{
}

TitlePlayer::~TitlePlayer()
{
}

bool TitlePlayer::Start()
{
	m_PlayerSkin = NewGO<SkinModelRender>(0,"player");
	m_PlayerSkin->Init(L"UnityChan.cmo");

	IsLeft = true;
	m_Angle = -90.0f;
	m_Rot.SetRotationDeg(CVector3::Up(), m_Angle);
	m_PlayerSkin->SetRotation(m_Rot);

	AnimationClip AniCli[AnimationPattern::AnimeNum];	
	AniCli[Idol].Load(L"Assets/animData/wait.tka");
	AniCli[Run].Load(L"Assets/animData/run.tka");
	m_Anime.Init(m_PlayerSkin->GetSkinModel(), AniCli, AnimationPattern::AnimeNum);

	return true;
}

void TitlePlayer::Update()
{
	int AnimeNo=Idol;
	float MoveSpeed = 5.0f;
	//左右のボタンでプレイヤーを動かします。
	if (g_Pad[0].IsPress(enButtonRight))
	{
		m_Pos.x -= MoveSpeed;
		AnimeNo = Run;
		IsLeft = false;
	}
	if (g_Pad[0].IsPress(enButtonLeft))
	{
		m_Pos.x += MoveSpeed;
		AnimeNo = Run;
		IsLeft = true;
	}
	if (IsLeft) {
		m_Angle -= 10.0f;
		if (m_Angle < -90.0f) {
			m_Angle = -90.0f;
		}
	}
	else {

		m_Angle += 10.0f;
		if (m_Angle < 90.0f) {
			m_Angle = 90.0f;
		}
	}
		m_Rot.SetRotationDeg(CVector3::Up(), m_Angle);
	m_Anime.Play(AnimeNo,1.0f/60.0f);
}
