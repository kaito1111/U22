/// <summary>
/// �G���W��
/// </summary>
/// <remarks>
/// �e�@�\�̃C���X�^���X�̎擾�Ƃ��A
/// �G���W�����N�������鏀���Ƃ����낢��
/// </remarks>

#pragma once
#include "graphics/GraphicsEngine.h"
#include "Sound/SoundEngine.h"
#include "CEffectEngine.h"

namespace myEngine {
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		/// <summary>
		/// ������
		/// </summary>
		void Init();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// �G���W���̃V���O���g���ł��B
		/// </summary>
		static CEngine& GetInstance()
		{
			//�V���O���g���̏���
			static CEngine* instance = nullptr;
			if (instance == nullptr) {
				instance = new CEngine;
			}
			return *instance;
		}
		/// <summary>
		/// �O���t�B�b�N�G���W���̎擾
		/// </summary>
		/// <returns>�O���t�B�b�N�G���W��</returns>
		GraphicsEngine& GetGraphicsEngine()
		{
			return m_graphicsEngine;
		}
		/// <summary>
		/// �T�E���h�G���W���̎擾
		/// </summary>
		/// <returns></returns>
		SoundEngine& GetSoundEngine()
		{
			return m_soundEngine;
		}
		/// <summary>
		/// �G�t�F�N�g�G���W���擾�B
		/// </summary>
		/// <returns></returns>
		CEffectEngine& GetEffectEngine()
		{
			return m_effectEngine;
		}

	private:
		GraphicsEngine			m_graphicsEngine;	//�O���t�B�b�N�G���W��
		SoundEngine				m_soundEngine;		//�T�E���h�G���W��
		CEffectEngine			m_effectEngine;		//�G�t�F�N�g�G���W��
	};	

	/// <summary>
	/// �G���W�����擾
	/// </summary>
	/// <returns>�G���W��</returns>
	static inline CEngine& Engine()
	{
		return CEngine::GetInstance();
	}
	/// <summary>
	/// �G���W������O���t�B�b�N�G���W�����擾
	/// </summary>
	/// <returns>�O���t�B�b�N�G���W��</returns>
	static inline GraphicsEngine& graphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
	/// <summary>
	/// �G���W������T�E���h�G���W���̎擾
	/// </summary>
	/// <returns></returns>
	static inline SoundEngine& soundEngine()
	{
		return Engine().GetSoundEngine();
	}
	/// <summary>
	/// �G�t�F�N�g�G���W���擾
	/// </summary>
	/// <returns></returns>
	static inline CEffectEngine& EffectEngineObj()
	{
		return Engine().GetEffectEngine();
	}
}

