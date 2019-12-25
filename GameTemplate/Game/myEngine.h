/// <summary>
/// �G���W��
/// </summary>
/// <remarks>
/// �e�@�\�̃C���X�^���X�̎擾�Ƃ��A
/// �G���W�����N�������鏀���Ƃ����낢��
/// </remarks>

#pragma once
#include "graphics/GraphicsEngine.h"

namespace myEngine {
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		/// <summary>
		/// �G���W���̃V���O���g���ł��B
		/// </summary>
		/// <returns>�G���W��</returns>
		/// <remarks>
		/// �G���W���̃C���X�^���X�͈�������Ȃ��悤�ɂȂ��Ă܂��B
		/// </remarks>
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

	private:
		GraphicsEngine			m_graphicsEngine;	//�O���t�B�b�N�G���W��
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
	/// �O���t�B�b�N�G���W�����擾
	/// </summary>
	/// <returns>�O���t�B�b�N�G���W��</returns>
	static inline GraphicsEngine& graphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
}

