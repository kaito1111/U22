#include "stdafx.h"
#include "StageSelect/TitleStage.h"


TitleStage::TitleStage()
{
}


TitleStage::~TitleStage()
{
}

bool TitleStage::Start()
{
	
	m_copymainRendrTarget.Init(
		g_graphicsEngine->GetOffScreenRenderTarget()->GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//�X�e�[�W���̑����f��
	m_floorModel.Init(L"Assets/modelData/serectStage.cmo");//��
	
	return true;
}

void TitleStage::Update()
{
	physics.CreateMeshObject(m_floorModel, m_floorPos, CQuaternion::Identity());
}
void TitleStage::Draw()
{
	//���������܂Ƃ��ȃX�e�[�W�I����ʂ���肽��
	//���[���h�s��̍X�V
	m_floorModel.UpdateWorldMatrix(m_floorPos, CQuaternion::Identity(), CVector3::One());
	/*skyModel.UpdateWorldMatrix({ 0,0,2000 }, CQuaternion::Identity(), { 1,1,1 });
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_scale);
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);*/

	m_floorModel.Draw(
	g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
		);
	/*m_model.Draw(
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
	);*/

}

void TitleStage::PostRender()
{
	m_copymainRendrTarget.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_copymainRendrTarget.Draw(g_camera2D.GetViewMatrix(), g_camera2D.GetProjectionMatrix());
}