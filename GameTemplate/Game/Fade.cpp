#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
{
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	m_LoadUp = NewGO<SpriteRender>(0);
	m_LoadUp->Init(L"Assets/sprite/LoadScreen(Up).dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_LoadDown = NewGO<SpriteRender>(0);
	m_LoadDown->Init(L"Assets/sprite/LoadScreen(Down).dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_SSprite = NewGO<SpriteRender>(0);
	m_SSprite->Init(L"Assets/sprite/LoadS.dds", 200.0f, 200.0f);
	m_SSprite->SetPosition(m_SPos);
	m_NSprite = NewGO<SpriteRender>(0);
	m_NSprite->Init(L"Assets/sprite/LoadN.dds", 200.0f, 200.0f);
	m_NSprite->SetPosition(m_NPos);
	CVector3 LoadUpPos = m_NPos;
	LoadUpPos.x += 100.0f;
	m_LoadUp->SetPosition(LoadUpPos);
	CVector3 LoadDownPos = m_SPos;
	LoadDownPos.x -= 100.0f;
	m_LoadDown->SetPosition(LoadDownPos);
}

Fade::~Fade()
{
	DeleteGO(m_SSprite);
	DeleteGO(m_NSprite);
	DeleteGO(m_LoadDown);
	DeleteGO(m_LoadUp);
}

void Fade::Update()
{
	float moveSpeed = 3.0f;
	if (m_SPos.x > 100.0f) {
		m_SPos.x -= moveSpeed;
		m_NPos.x += moveSpeed;
	}
	else {
		if (m_angle < 180.0f) {
			m_angle++;
			CQuaternion SRot = CQuaternion::Identity();
			SRot.SetRotationDeg(CVector3::AxisZ(), -m_angle);
			m_SSprite->SetRotation(SRot);
			CQuaternion NRot = CQuaternion::Identity();
			NRot.SetRotationDeg(CVector3::AxisZ(), m_angle);
			m_NSprite->SetRotation(NRot);
		}
	}
	if (m_SPos.y < 0.0f) {
		m_SPos.y += moveSpeed;
		m_NPos.y -= moveSpeed;
	}
	if (m_angle >= 180) {
		if (m_SPos.x > 360.0f) {
			m_SPos.y -= moveSpeed * 2;
			m_NPos.y += moveSpeed * 2;
		}
		m_SPos.x += moveSpeed * 2;
		m_NPos.x -= moveSpeed * 2;
	}
	m_SSprite->SetPosition(m_SPos);
	m_NSprite->SetPosition(m_NPos);
	CVector3 LoadUpPos = m_NPos;
	LoadUpPos.x += 100.0f;
	m_LoadUp->SetPosition(LoadUpPos);
	CVector3 LoadDownPos = m_SPos;
	LoadDownPos.x -= 100.0f;
	m_LoadDown->SetPosition(LoadDownPos);
	CVector3 SNDiff = m_SPos - m_NPos;
	m_DiffLengh = SNDiff.Length();
}
void Fade::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}