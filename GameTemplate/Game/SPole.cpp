#include "stdafx.h"
#include "SPole.h"

#include "NPole.h"
#include "Player.h"

SPole::SPole()
{
	m_model.Init(L"Assets/modelData/SPole.cmo");
}

SPole::~SPole()
{
}

bool SPole::Start()
{
	m_npole = FindGO<NPole>("npole");
	m_player = FindGO<Player>("player");
	return true;
}

void SPole::Update()
{
	idou();
	//deleteRange();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
}

void SPole::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void SPole::deleteRange()
{
	CVector3 playerDir = m_player->GetPosition() - m_position;
	if (playerDir.Length() > 100.0f) {
		DeleteGO(this);
	}
}

void SPole::magunetTask(CVector3& Position)
{
	CVector3 pullDir = Position - m_position;
	if (pullDir.Length() < 50.0f) {
		pullDir.Normalize();
		Position -= pullDir;
	}
}

void SPole::idou()
{
	CVector3 oldPos = m_position;
	float diff = oldPos.Length() - m_position.Length();
	if (0.001f > diff && -0.001f < diff) {
		magunetTask(m_position);
	}
}
