#include "stdafx.h"
#include "Magnet.h"

Magnet::Magnet()
{
}

Magnet::~Magnet()
{
}

void Magnet::MagnetTask()
{
	switch (state)
	{
	case Magnet::NMode:
		MagnetManeger().QueryObject([&](Magnet* mag)->bool
			{
			if (mag->GetMagnet() == Magnet::NMode) {

			}
			return;
			}
		);
		break;
	case Magnet::SMode:
		break;
	case Magnet::NoMode:
		break;
	default:
		break;
	}
}
