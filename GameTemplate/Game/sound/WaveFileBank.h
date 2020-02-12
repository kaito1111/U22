/// <summary>
/// 波形データバンク
/// </summary>

#pragma once

#include <map>
#include <memory>
class WaveFile;
//Waveファイルとポインタの共有
using WaveFilePtr = std::shared_ptr<WaveFile>;
//Waveファイルマップの作成
using WaveFilePtrMap = std::map<unsigned int, WaveFilePtr>;

/// <summary>
/// 波形データバンク
/// </summary>
/// <remarks>
/// 一度ロードされた波形データをバンクに登録することができる
/// 登録された波形データは再度ロードすることなく、使用できます
/// </remarks>
class WaveFileBank
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WaveFileBank();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WaveFileBank();
	/// <summary>
	/// 波形データの登録
	/// </summary>
	/// <param name="groupID">グループID。最大値MaxGroup-1</param>
	/// <param name="waveFile">波形データ</param>
	void RegistWaveFile(int groupID, WaveFilePtr waveFile);
	/// <summary>
	/// 引数で指定したファイルパスが登録されているかの検索
	/// </summary>
	/// <param name="groupID">グループID。最大値MaxGroup-1</param>
	/// <param name="filePath">検索したいファイルパス</param>
	/// <returns>登録されていなかったらnull</returns>
	WaveFilePtr FindWaveFile(int groupID, const wchar_t* filePath);
	/// <summary>
	/// 波形データをバンクから登録解除
	/// </summary>
	/// <param name="groupID">グループID。最大値MaxGroup-1</param>
	/// <param name="waveFile">波形データ</param>
	void UnregistWaveFile(int groupID, WaveFilePtr waveFile);
	/// <summary>
	/// グループ単位での解放
	/// </summary>
	/// <param name="groupID">グループID。最大値MaxGroup-1</param>
	void Release(int groupID);
	/// <summary>
	/// すべて解放
	/// </summary>
	void ReleaseAll()
	{
		for (int i = 0; i < MAX_GROUP; i++) {
			Release(i);
		}
	}

private:
	static const int MAX_GROUP = 256;
	WaveFilePtrMap m_waveFileMap[MAX_GROUP];	//波形データのリスト

};

