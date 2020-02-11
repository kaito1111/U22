/// <summary>
/// �g�`�f�[�^�o���N
/// </summary>

#pragma once

#include <map>
#include <memory>
class WaveFile;
//Wave�t�@�C���ƃ|�C���^�̋��L
using WaveFilePtr = std::shared_ptr<WaveFile>;
//Wave�t�@�C���}�b�v�̍쐬
using WaveFilePtrMap = std::map<unsigned int, WaveFilePtr>;

/// <summary>
/// �g�`�f�[�^�o���N
/// </summary>
/// <remarks>
/// ��x���[�h���ꂽ�g�`�f�[�^���o���N�ɓo�^���邱�Ƃ��ł���
/// �o�^���ꂽ�g�`�f�[�^�͍ēx���[�h���邱�ƂȂ��A�g�p�ł��܂�
/// </remarks>
class WaveFileBank
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	WaveFileBank();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WaveFileBank();
	/// <summary>
	/// �g�`�f�[�^�̓o�^
	/// </summary>
	/// <param name="groupID">�O���[�vID�B�ő�lMaxGroup-1</param>
	/// <param name="waveFile">�g�`�f�[�^</param>
	void RegistWaveFile(int groupID, WaveFilePtr waveFile);
	/// <summary>
	/// �����Ŏw�肵���t�@�C���p�X���o�^����Ă��邩�̌���
	/// </summary>
	/// <param name="groupID">�O���[�vID�B�ő�lMaxGroup-1</param>
	/// <param name="filePath">�����������t�@�C���p�X</param>
	/// <returns>�o�^����Ă��Ȃ�������null</returns>
	WaveFilePtr FindWaveFile(int groupID, const wchar_t* filePath);
	/// <summary>
	/// �g�`�f�[�^���o���N����o�^����
	/// </summary>
	/// <param name="groupID">�O���[�vID�B�ő�lMaxGroup-1</param>
	/// <param name="waveFile">�g�`�f�[�^</param>
	void UnregistWaveFile(int groupID, WaveFilePtr waveFile);
	/// <summary>
	/// �O���[�v�P�ʂł̉��
	/// </summary>
	/// <param name="groupID">�O���[�vID�B�ő�lMaxGroup-1</param>
	void Release(int groupID);
	/// <summary>
	/// ���ׂĉ��
	/// </summary>
	void ReleaseAll()
	{
		for (int i = 0; i < MAX_GROUP; i++) {
			Release(i);
		}
	}

private:
	static const int MAX_GROUP = 256;
	WaveFilePtrMap m_waveFileMap[MAX_GROUP];	//�g�`�f�[�^�̃��X�g

};

