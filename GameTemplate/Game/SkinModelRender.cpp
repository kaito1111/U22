#include "stdafx.h"
#include "SkinModelRender.h"

void myEngine::SkinModelRender::Init(
	wchar_t* filePath,
	AnimationClip * animationClips, 
	int numAnimationClips)
{
	wchar_t StandardfilePach[256] = L"Assets/modeldata/";
	wcscat(StandardfilePach, filePath);
	m_skinModel.Init(StandardfilePach);
	InitAnimation(animationClips, numAnimationClips);
}

void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
{
	m_animationClips = animationClips;
	m_numAnimationClips = numAnimationClips;
	if (m_animationClips != nullptr) {
		m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
	}
}

bool myEngine::SkinModelRender::Start()
{
	return true;
}

void myEngine::SkinModelRender::Update()
{
	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void myEngine::SkinModelRender::Draw()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		Silhouette
	);
}
