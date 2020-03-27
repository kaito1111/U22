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
	m_model.Init(L"Asset/modelData/stage_oreore.cmo");
	m_model2.Init(L"Asset/modelData/stageDossun.cmo");
	return true;
}

void TitleStage::Update()
{
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), m_scale);
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);
}
