#include "stdafx.h"
#include "Stage.h"



Stage::Stage()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/stage_00.cmo");
	m_phyStaticObuject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
}


Stage::~Stage()
{

}

void Stage::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	//�o���b�g�t�B�W�b�N�X���o������`�F�b�N�|�C���g�̃V�X�e�������
}

void Stage::Draw()
{
	//m_model.Draw(
	//	g_camera3D.GetViewMatrix(),
	//	g_camera3D.GetProjectionMatrix()
	//);
}