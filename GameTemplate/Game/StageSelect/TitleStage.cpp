#include "stdafx.h"
#include "StageSelect/TitleStage.h"


TitleStage::TitleStage()
{
	//if (m_IsClear1) {
	//	m_Iwa = NewGO<Iwa>(0, "iwa");
	//	m_Iwa->SetPos({ 0.0f,0.0f,0.0f });
	//}
}


TitleStage::~TitleStage()
{
}

bool TitleStage::Start()
{

	//ステージその他モデル
	m_floorModel.Init(L"Assets/modelData/serectStage.cmo");//床
	
	m_SpriteScale = CVector3::One() * 0.8f;

	skyModel = NewGO<SkinModelRender>(3);
	skyModel->Init(L"Player.cmo");
	
	float SWAH = 300.0f;
	m_Stage1Sprite = NewGO<SpriteRender>(2);
	m_Stage1Sprite->Init(L"Assets/sprite/Corse1_image.dds", SWAH, SWAH, true);
	m_Stage1Sprite->SetPosition(m_Sprite1Pos);
	m_Stage1Sprite->SetScale(m_SpriteScale);
	
	m_Stage2Sprite = NewGO<SpriteRender>(2);
	m_Stage2Sprite->Init(L"Assets/sprite/Corse2_image.dds", SWAH, SWAH, true);
	m_Stage2Sprite->SetPosition(m_Sprite2Pos);
	m_Stage2Sprite->SetScale(m_SpriteScale);

	float SSWAH = 320.0f;
	m_SelectSprite = NewGO<SpriteRender>(1);
	m_SelectSprite->Init(L"Assets/sprite/Yellow.dds", SSWAH, SSWAH, true);
	m_SelectSprite->SetPosition(m_Sprite2Pos);
	m_SelectSprite->SetScale(CVector3::Zero());

	return true;
}

void TitleStage::Update()
{
	m_SpriteScale = CVector3::One() * 0.8f;
	m_SelectSprite->SetScale(CVector3::Zero());

	CVector3 PlPos = CVector3::Zero();
	CVector3 diff1 = PlPos - m_Sprite1Pos;
	if (diff1.Length() < 150.0f) {
		m_Stage1Sprite->SetScale(CVector3::One());
		m_SelectSprite->SetPosition(m_Sprite1Pos);
		m_SelectSprite->SetScale(CVector3::One());
	}

	CVector3 diff2 = PlPos - m_Sprite2Pos;
	if (diff2.Length() < 150.0f) {
		m_Stage2Sprite->SetScale(CVector3::One());
		m_SelectSprite->SetPosition(m_Sprite2Pos);
		m_SelectSprite->SetScale(CVector3::One());
	}

	m_Stage2Sprite->SetScale(m_SpriteScale);
	m_Stage1Sprite->SetScale(m_SpriteScale);
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
