#include "stdafx.h"
#include "TitleStage.h"


TitleStage::TitleStage()
{
}


TitleStage::~TitleStage()
{
}

bool TitleStage::Start()
{
	//�X�e�[�W�̃��x���z�u�O�̏��
	skyModel.Init(L"Assets/modelData/sky.cmo");     //�N�\�G���w�i
	m_model.Init(L"Assets/modelData/stage_00.cmo"); //�X�e�[�W1�D
	m_model2.Init(L"Assets/modelData/stage3.cmo");	//�X�e�[�W�V�D���������V����
	return true;
}

void TitleStage::Update()
{
	
	skyModel.UpdateWorldMatrix({0,0,2000}, CQuaternion::Identity(), { 1,1,1 });
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_scale);
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);
}

void TitleStage::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
	m_model2.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
	skyModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}
