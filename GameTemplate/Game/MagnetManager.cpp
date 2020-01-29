#include "stdafx.h"
#include "MagnetManager.h"

MagnetManager::MagnetManager() 
{
}
MagnetManager::~MagnetManager()
{
}

void MagnetManager::LearnObject(Magnet* magnet)
{
	m_MagnetList.push_back(magnet);
}

void MagnetManager::FindObject(std::function < bool(Magnet*mag) > func)
{
	for (auto MagnetList : m_MagnetList) {
		if ( func( MagnetList ) == false )
		{
			return;
		}
	}
}

void MagnetManager::QueryObject(std::function<bool(Magnet*mag)> func)
{
	FindObject(func);
}

