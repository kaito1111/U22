#include "stdafx.h"
#include "KaitoTask.h"
#include "TwoP_Pad.h"
#include "GameCamera.h"
#include "Goal.h"
#include "Gimmick_Button.h"

KaitoTask::KaitoTask()
{
}

KaitoTask::~KaitoTask()
{
}

bool KaitoTask::Start()
{
	NewGO<TwoP_Pad>(0, "pad");
	NewGO<GameCamera>(1, "camera");
	//NewGO<Goal>(1, "goal");
	return true;
}
