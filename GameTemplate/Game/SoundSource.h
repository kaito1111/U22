#pragma once
class SoundSource
{
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	SoundSource();
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~SoundSource();
//
//	/// <summary>
//	/// 初期化（オンメモリ）
//	/// <para>小さなサイズのオーディオ(効果音とか)はここっちで基本的に再生！</para>
//	/// </summary>
//	/// <param name="filePath">ファイルパス</param>
//	void Init(wchar_t* filePath);
//	/// <summary>
//	/// 初期化(ストリーミング再生)
//	/// <para>大きなサイズのオーディオ(BGMとか)はこっちを基本的に再生！</para>
//	/// </summary>
//	/// <remarks>
//	///	リングバッファにストリーミング読み込みを行って、再生を行っていきます。
//	/// 一度に読み込まれるデータの最大サイズはbufferingSizeです。
//	/// 読み込まれたデータはリングバッファにコピーされていきます。
//	/// </remarks>
//	/// <param name="filePath">ファイルパス</param>
//	/// <param name="ringBufferSize">リングバッファのサイズ。(bufferSizeの倍数になっていると無駄なく活用できます。)</param>
//	/// <param name="bufferingSize">ストリーミングの最大バッファリングサイズ。</param>
//	void initStreaming(wchar_t* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
//	/// <summary>
//	/// 解放
//	/// </summary>
//	void Release();
//	/// <summary>
//	/// 再生
//	/// <para>isLoopがfalseなら一回のみの再生！</para>
//	/// </summary>
//	/// <param name="isLoop"></param>
//	void Play(bool isLoop);
//	/// <summary>
//	/// 停止
//	/// </summary>
//	void Stop()
//	{
//		//停止
//		m_sourceVoice->Stop();
//		m_isPlaying = false;
//	}
//	/// <summary>
//	/// 一時停止
//	/// </summary>
//	void Pause()
//	{
//		//停止
//		m_sourceVoice->Stop();
//	}
//	/// <summary>
//	/// 再生中かの判定
//	/// </summary>
//	/// <returns></returns>
//	bool IsPlaying() const
//	{
//		return m_isPlaying;
//	}
//	/// <summary>
//	/// ボリュームの設定
//	/// </summary>
//	/// <param name="vol">ボリューム</param>
//	void SetVolume(float vol)
//	{
//		m_sourceVoice->SetVolume(vol);
//	}
//	/// <summary>
//	/// ボリュームの取得
//	/// </summary>
//	/// <returns></returns>
//	float GetVolume() const
//	{
//		float vol;
//		m_soundVoice->GetVolume(&vol);
//		return vol;
//	}
//	/// <summary>
//	/// ループフラグの取得
//	/// </summary>
//	/// <returns></returns>
//	bool GetLoopFlag() const
//	{
//		return m_isLoop;
//	}
//	/// <summary>
//	/// ボイスの周波数調整比
//	/// </summary>
//	/// <remarks>
//	/// 詳細はIXAudio2SourceVoiceのSetFrequencyRatioを参照してください。
//	/// </remarks>
//	/// <param name="ratio">周波数比</param>
//	void SetFrequencyRatio(float ratio)
//	{
//		if (m_sourceVoice != nullptr) {
//			m_sourceVoice->SetFrequencyRatio(ratio);
//		}
//	}
//	IXAudio2SourceVoice* GetXAudio2SourceVoice()
//	{
//		return m_sourceVoice;
//	}
//	//int GetNumInputChannel()const
//	//{
//	//	return m_waveFile->GetFormat()->nChannels;
//	//}
//	//FLOAT32* GetEmitterAzimuths()
//	//{
//	//	return m_emitterAzimuths;
//	//}
//	//FLOAT32* GetMatrixCoefficients()
//	//{
//	//	return m_matrixCoefficients;
//	//}
//
//	/// <summary>
//	/// 更新
//	/// </summary>
//	void Update();
//private:
//	void InitCommon();
//	//ストリーミング再生中の更新
//	void UpdateStreaming();
//	//オンメモリ再生中の更新
//	void UpdateOnMemory();
//	void Play(char* buff, unsigned int bufferSize);
//	void StartStreamingBuffring();
//
//private:
//	enum EnStreamingStatus {
//		enStreamingBuffering,	//バッファリング
//		enStreamngQueueing,		//キューイング
//	};
//	//std::shared_ptr<CWaveFile>	m_waveFile;
//	IXAudio2SourceVoice*			m_sourceVoice = nullptr;		//ソースボイス
//	bool							m_isLoop = false;				//ループフラグ	
//	bool							m_isPlaying = false;			//再生中フラグ
//	bool							m_isStreaming = false;			//ストリーミング再生
//	unsigned int					m_streamingBufferSize = 0;		//ストリーミング用バッファリングサイズ
//	unsigned int					m_currentBufferSize = 0;		//現在のバッファリングサイズ
//	unsigned int					m_readStartPos = 0;				//読み込み開始位置
//	unsigned int					m_ringBufferSize = 0;			//リングバッファサイズ
//	EnStreamingStatus				m_streamingState = enStreamingBuffering;
//	//FLOAT32							m_emitterAzimuths[INPUTCHANNELS]
//	//FLOAT32							m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];
//	bool							m_isAvailable = false;			//初期化
};

