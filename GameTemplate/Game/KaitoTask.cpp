#include "stdafx.h"
#include "KaitoTask.h"
#include "TwoP_Pad.h"
#include "GameCamera.h"
#include "stageObject/Goal.h"
#include "stageObject/Gimmick_Button.h"

KaitoTask::KaitoTask()
{
	NewGO<TwoP_Pad>(5, "pad");
	NewGO<GameCamera>(1, "camera");
	//NewGO<Goal>(1, "goal");
}

KaitoTask::~KaitoTask()
{
}