#include "stdafx.h"
#include "stageObject2.h"
#include"Player.h"

stageObject2::stageObject2()
{
	m_model->Init(L"Aseet/modelData/maruToge.cmo");

}


stageObject2::~stageObject2()
{
}

bool stageObject2::Start()
{

	return true;
}

void stageObject2::Update()
{
}