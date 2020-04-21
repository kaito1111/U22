#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
{
	m_copyMainRtToFrameBufferSprite.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	m_SSprite = NewGO<SpriteRender>(0);
	m_SSprite->Init(L"Assets/sprite/LoadS.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_NSprite = NewGO<SpriteRender>(0);
	m_NSprite->Init(L"Assets/sprite/LoadN.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
}

Fade::~Fade()
{
	DeleteGO(m_SSprite);
	DeleteGO(m_NSprite);
}

void Fade::Update()
{

}

void Fade::PostRender()
{
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix(), 1.0f);
}
