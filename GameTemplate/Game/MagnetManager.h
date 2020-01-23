#pragma once
#include "SPole.h"
#include "NPole.h"

class MagnetManager: public SPole ,public NPole,public IGameObject
{
	bool Start()override;
	void Update()override;
	
};

