#include "stdafx.h"
#include "MagnetManager.h"

MagnetManager::MagnetManager() 
{
}
MagnetManager::~MagnetManager()
{
}

void MagnetManager::LearnMagetObject(Magnet* magnetObject , CVector3 pos)
{
	m_MagnetList.push_back(magnetObject);
	magnetObject->SetPosition(&pos);
}

void MagnetManager::FindMagnetObject(std::function < bool(Magnet*mag) > func)
{
	for (auto MagnetList : m_MagnetList) {
		if ( func( MagnetList ) == false )
		{
			return;
		}
	}
}

void MagnetManager::QueryMagnetObject(std::function<bool(Magnet*mag)> func)
{
	FindMagnetObject(func);
}

