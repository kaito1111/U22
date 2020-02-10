#include "stdafx.h"
#include "KaitoTask.h"
#include "TwoP_Pad.h"
#include "GameCamera.h"

KaitoTask::KaitoTask()
{
}

KaitoTask::~KaitoTask()
{
}

bool KaitoTask::Start()
{
	NewGO<TwoP_Pad>(3, "pad");
	NewGO<GameCamera>(1, "camera");
	return true;
}
