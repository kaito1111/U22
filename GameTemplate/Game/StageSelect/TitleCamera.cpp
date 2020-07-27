#include "stdafx.h"
#include "StageSelect/TitleCamera.h"
#include "Player.h"
#include "StageSelect.h"
TitleCamera::TitleCamera()
{
}

TitleCamera::~TitleCamera()
{
}

bool TitleCamera::Start()
{
	//�J�������������B
	g_camera3D.SetPosition({ 320.0f, 240.0f,-1110.0f });
	g_camera3D.SetTarget(CVector3::Zero());
	g_camera3D.SetFar(10000.0f);
	g_camera3D.SetNear(1.0f);
	g_camera3D.Update();
	m_target = CVector3::Zero();
	//player = FindGO<Player>("player1");
	return true;
}

void TitleCamera::Update()
{
	Move();


	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_pos);
	//�J�����̍X�V�B
	g_camera3D.Update();
}

void TitleCamera::Move()
{
	static const float width = 640.0f;     //��
	static const float camTargetLen = -1000; //�J�����̒����_�܂ł̋���
	static const float texchaHigh = 240.0f;//�e�N�X�`���̍����̔���
	//m_target = g_camera3D.GetForward();
	m_pos.z = camTargetLen;

	m_pos.y = texchaHigh;

	if (g_Pad[0].IsTrigger(enButtonRight) && nowChoiceStage < g_StageMAX)
	{
		nowChoiceStage++;
		m_pos.x += width;
	}
	if (g_Pad[0].IsTrigger(enButtonLeft) && nowChoiceStage > 0)
	{
		nowChoiceStage--;
		m_pos.x -= width;
	}
}
