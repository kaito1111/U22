/// <summary>
/// �G���W��
/// </summary>
/// <remarks>
/// �e�@�\�̃C���X�^���X�̎擾�Ƃ��A
/// �G���W�����N�������鏀���Ƃ����낢��
/// </remarks>

#pragma once
#include "graphics/GraphicsEngine.h"
#include "sound/soundengine.h"
#include "Effect/CEffectEngine.h"
#include "util/tkStopwatch.h"
#include "graphics/2D/Font.h"
#include "TwoP_Pad.h"

namespace myEngine {
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		/// <summary>
		/// �X�^�[�g
		/// </summary>
		/// <returns></returns>
		bool Start();
		/// <summary>
		/// ������
		/// </summary>
		void Init();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// �G���W���I������
		/// </summary>
		void Final();
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
		/// <summary>
		/// �X�g�b�v�E�H�b�`�擾�B
		/// </summary>
		/// <returns></returns>
		CStopwatch& getSW()
		{
			return m_sw;
		}
		/// <summary>
		/// 2�̃p�b�h�̎擾�B
		/// </summary>
		/// <returns></returns>
		TwoP_Pad& GetTwoP_Pad()
		{
			return m_twoP_Pad;
		}
	private:
		//�G���W���֘A
		GraphicsEngine			m_graphicsEngine;		//�O���t�B�b�N�G���W��
		SoundEngine				m_soundEngine;			//�T�E���h�G���W��
		CEffectEngine			m_effectEngine;			//�G�t�F�N�g�G���W��
		//����
		CStopwatch				m_sw;					//�X�g�b�v�E�H�b�`
		TwoP_Pad				m_twoP_Pad;				//�Q�v���C���[�̃p�b�h�̊Ǘ��I�u�W�F�N�g(�ɂ������ò�j
	private:
		//fps�\���֘A
		float					m_timeTotal = 0;		//���v���ԁB
		float					m_fps = 0;				//FPS�B
		std::unique_ptr<CFont>	m_font;					//�t�H���g�B

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

