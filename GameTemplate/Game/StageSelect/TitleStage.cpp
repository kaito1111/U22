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
	//ステージその他モデル
	m_floorModel.Init(L"Assets/modelData/serectStage.cmo");//床
	skyModel = NewGO<SkinModelRender>(0);
	skyModel->Init(L"Assets/modelData/Player.cmo");
	m_Stage1Sprite = NewGO<SpriteRender>(0);
	m_Stage1Sprite->Init(L"Assets/sprite/Corse1_image.dds", 300.0f, 300.0f);
	//m_Stage2Sprite = NewGO<SpriteRender>(0);
	//m_Stage2Sprite->Init(L"Assets/sprite/")
		return true;
}

void TitleStage::Update()
{
	physics.CreateMeshObject(m_floorModel, m_floorPos, CQuaternion::Identity());
}
void TitleStage::Draw()
{
	//もう少しまともなステージ選択画面を作りたい
	//ワールド行列の更新
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
