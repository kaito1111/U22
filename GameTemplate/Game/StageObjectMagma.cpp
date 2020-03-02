#include "stdafx.h"
#include "StageObjectMagma.h"
#include"Player.h"

StageObjectMagma::StageObjectMagma()
{
	//�}�O�}�ɂȂ�\��Ȃ񂾁B�\�肾���ǁB
}


StageObjectMagma::~StageObjectMagma()
{
}

bool StageObjectMagma::Start()
{
	m_pos.y -= 400.0f;
	m_model.Init(L"Assets/modelData/magma.cmo");
	return true;
}

void StageObjectMagma::Update()
{
	PlayerKill();
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
}

void StageObjectMagma::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void StageObjectMagma::PlayerKill()
{
	//�v���C���[�L���Ƃ������Ă邯�ǁA
	//�����������������ɂ�����
	const float upSpeed = 0.2f;
	m_pos.y += upSpeed;

	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 1.0f);
	m_rot.Multiply(qRot);
}