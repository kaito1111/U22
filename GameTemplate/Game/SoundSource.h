#pragma once
class SoundSource
{
//	/// <summary>
//	/// �R���X�g���N�^
//	/// </summary>
//	SoundSource();
//	/// <summary>
//	/// �f�X�g���N�^
//	/// </summary>
//	~SoundSource();
//
//	/// <summary>
//	/// �������i�I���������j
//	/// <para>�����ȃT�C�Y�̃I�[�f�B�I(���ʉ��Ƃ�)�͂��������Ŋ�{�I�ɍĐ��I</para>
//	/// </summary>
//	/// <param name="filePath">�t�@�C���p�X</param>
//	void Init(wchar_t* filePath);
//	/// <summary>
//	/// ������(�X�g���[�~���O�Đ�)
//	/// <para>�傫�ȃT�C�Y�̃I�[�f�B�I(BGM�Ƃ�)�͂���������{�I�ɍĐ��I</para>
//	/// </summary>
//	/// <remarks>
//	///	�����O�o�b�t�@�ɃX�g���[�~���O�ǂݍ��݂��s���āA�Đ����s���Ă����܂��B
//	/// ��x�ɓǂݍ��܂��f�[�^�̍ő�T�C�Y��bufferingSize�ł��B
//	/// �ǂݍ��܂ꂽ�f�[�^�̓����O�o�b�t�@�ɃR�s�[����Ă����܂��B
//	/// </remarks>
//	/// <param name="filePath">�t�@�C���p�X</param>
//	/// <param name="ringBufferSize">�����O�o�b�t�@�̃T�C�Y�B(bufferSize�̔{���ɂȂ��Ă���Ɩ��ʂȂ����p�ł��܂��B)</param>
//	/// <param name="bufferingSize">�X�g���[�~���O�̍ő�o�b�t�@�����O�T�C�Y�B</param>
//	void initStreaming(wchar_t* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
//	/// <summary>
//	/// ���
//	/// </summary>
//	void Release();
//	/// <summary>
//	/// �Đ�
//	/// <para>isLoop��false�Ȃ���݂̂̍Đ��I</para>
//	/// </summary>
//	/// <param name="isLoop"></param>
//	void Play(bool isLoop);
//	/// <summary>
//	/// ��~
//	/// </summary>
//	void Stop()
//	{
//		//��~
//		m_sourceVoice->Stop();
//		m_isPlaying = false;
//	}
//	/// <summary>
//	/// �ꎞ��~
//	/// </summary>
//	void Pause()
//	{
//		//��~
//		m_sourceVoice->Stop();
//	}
//	/// <summary>
//	/// �Đ������̔���
//	/// </summary>
//	/// <returns></returns>
//	bool IsPlaying() const
//	{
//		return m_isPlaying;
//	}
//	/// <summary>
//	/// �{�����[���̐ݒ�
//	/// </summary>
//	/// <param name="vol">�{�����[��</param>
//	void SetVolume(float vol)
//	{
//		m_sourceVoice->SetVolume(vol);
//	}
//	/// <summary>
//	/// �{�����[���̎擾
//	/// </summary>
//	/// <returns></returns>
//	float GetVolume() const
//	{
//		float vol;
//		m_soundVoice->GetVolume(&vol);
//		return vol;
//	}
//	/// <summary>
//	/// ���[�v�t���O�̎擾
//	/// </summary>
//	/// <returns></returns>
//	bool GetLoopFlag() const
//	{
//		return m_isLoop;
//	}
//	/// <summary>
//	/// �{�C�X�̎��g��������
//	/// </summary>
//	/// <remarks>
//	/// �ڍׂ�IXAudio2SourceVoice��SetFrequencyRatio���Q�Ƃ��Ă��������B
//	/// </remarks>
//	/// <param name="ratio">���g����</param>
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
//	/// �X�V
//	/// </summary>
//	void Update();
//private:
//	void InitCommon();
//	//�X�g���[�~���O�Đ����̍X�V
//	void UpdateStreaming();
//	//�I���������Đ����̍X�V
//	void UpdateOnMemory();
//	void Play(char* buff, unsigned int bufferSize);
//	void StartStreamingBuffring();
//
//private:
//	enum EnStreamingStatus {
//		enStreamingBuffering,	//�o�b�t�@�����O
//		enStreamngQueueing,		//�L���[�C���O
//	};
//	//std::shared_ptr<CWaveFile>	m_waveFile;
//	IXAudio2SourceVoice*			m_sourceVoice = nullptr;		//�\�[�X�{�C�X
//	bool							m_isLoop = false;				//���[�v�t���O	
//	bool							m_isPlaying = false;			//�Đ����t���O
//	bool							m_isStreaming = false;			//�X�g���[�~���O�Đ�
//	unsigned int					m_streamingBufferSize = 0;		//�X�g���[�~���O�p�o�b�t�@�����O�T�C�Y
//	unsigned int					m_currentBufferSize = 0;		//���݂̃o�b�t�@�����O�T�C�Y
//	unsigned int					m_readStartPos = 0;				//�ǂݍ��݊J�n�ʒu
//	unsigned int					m_ringBufferSize = 0;			//�����O�o�b�t�@�T�C�Y
//	EnStreamingStatus				m_streamingState = enStreamingBuffering;
//	//FLOAT32							m_emitterAzimuths[INPUTCHANNELS]
//	//FLOAT32							m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];
//	bool							m_isAvailable = false;			//������
};

