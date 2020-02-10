/// <summary>
/// サウンドエンジンクラス::DirectXⅢ丸パクリ！
/// </summary>

#pragma once

class SoundEngine
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SoundEngine();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SoundEngine();
	/// <summary>
	///	初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 明示的な解放
	/// </summary>
	void Release();
	/// <summary>
	/// 更新
	/// </summary>
	//void Update();

private:
	//IXAudio2* m_xAudio2 = nullptr;
	//IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	//IUnknown* m_reverbEffect = nullptr;						//リバープエフェクト
	//IXAudio2SubmixVoice* m_submixVoice = nullptr;			//サブミックスボイス
	//DWORD m_channelMask = 0;								//オーディオチャンネル
	//DWORD m_nChannels = 0;									//チャンネル数
	//bool m_isInited = false;								//初期化したか
	//std::list<Sound
};

