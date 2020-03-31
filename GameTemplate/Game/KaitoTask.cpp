#include "stdafx.h"
#include "KaitoTask.h"
#include "TwoP_Pad.h"
#include "GameCamera.h"
#include "stageObject/Goal.h"
#include "stageObject/Gimmick_Button.h"

KaitoTask::KaitoTask()
{
}

KaitoTask::~KaitoTask()
{
}

bool KaitoTask::Start()
{
	NewGO<TwoP_Pad>(5, "pad");
	NewGO<GameCamera>(1, "camera");
	NewGO< Gimmick_Button>(0, nullptr);
	//NewGO<Goal>(1, "goal");
	return true;
}
