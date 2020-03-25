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
	m_model2.Init(L"Asset/modelData/stageDossun.cmo");
	return true;
}

void TitleStage::Update()
{
	m_model2.UpdateWorldMatrix(m_pos2, CQuaternion::Identity(), m_scale2);
}
