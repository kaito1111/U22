#include "stdafx.h"
#include "WaveFileBank.h"
#include "WaveFile.h"
#include "util/Util.h"

WaveFileBank::WaveFileBank()
{
}
WaveFileBank::~WaveFileBank()
{
	ReleaseAll();
}
void WaveFileBank::Release(int groupID)
{
	for (auto waveFile : m_waveFileMap[groupID]) {
		waveFile.second->Release();
	}
	//解放
	m_waveFileMap[groupID].clear();
}
void WaveFileBank::UnregistWaveFile(int groupID, WaveFilePtr waveFile)
{
	//リストから削除
	m_waveFileMap->erase(waveFile->GetFilePathHash());
}
void WaveFileBank::RegistWaveFile(int groupID, WaveFilePtr waveFile)
{
	//リストに追加
	m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
}
WaveFilePtr WaveFileBank::FindWaveFile(int groupID, const wchar_t* filePath)
{
	auto value = m_waveFileMap[groupID].find(Util::MakeHash(filePath));
	//検索
	if (value != m_waveFileMap[groupID].end()) {
		return value->second;
	}
	return WaveFilePtr();
}