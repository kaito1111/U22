/// <summary>
/// GameObject�̃}�l�[�W���[
/// </summary>
#pragma once
#include "IGameObject.h"
#include "util/Util.h"

namespace myEngine {
	typedef unsigned char	GameObjectPrio;
	class GameObjectManager
	{
	public:
		GameObjectManager()
		{
			m_gameObjectListArray.resize(10);
			m_deleteObjectArray[0].resize(10);
			m_deleteObjectArray[1].resize(10);
		};
		~GameObjectManager()
		{
		};
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̖��O�L�[���쐬
		/// </summary>
		/// <remarks>
		/// FindGO����Ƃ��Ɏg����
		/// Util::MakeHash�ŕ�����𐔗�(hash)�ɕς��Ă��܂�
		/// </remarks>
		/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
		/// <returns>�n�b�V���̒l</returns>
		static unsigned int MakeGameObjectNameKey(const char* objectName)
		{
			//�f�t�H���g�l�[������
			static const unsigned int defaultNameKey = Util::MakeHash("Undefined");
			unsigned int hash;
			//�Ȃɂ������ĂȂ��Ȃ�
			if (objectName == nullptr) {
				//�f�t�H���g�l�[��
				hash = defaultNameKey;
			}
			//�Ȃ񂩓����Ă���
			else {
				//�n�b�V���̍쐬
				hash = Util::MakeHash(objectName);
			}
			return hash;
		}
		/// <summary>
		/// �C���X�^���X�̎擾
		/// </summary>
		/// <returns>�C���X�^���X</returns>
		static GameObjectManager& Instance()
		{
			static GameObjectManager instance;
			return instance;
		}
	
	public:
		/*
		���b�v����O�̖{�̂̊֐��ł� �C�����C���֐��ł��B
		*/
		/// <summary>
		/// <para>�I�u�W�F�N�g�̍쐬</para>
		/// <para>���̊֐��ō�����I�u�W�F�N�g��DeleteGO�ŏ�������</para>
		/// </summary>
		template <class T>
		T* NewGameObject(GameObjPrio prio, const char* objectName)
		{
			(void*)objectName;
			//�N���X�̏�����
			T* newObject = new T();
			//�D��x+�Q�[���I�u�W�F�N�g�����X�g�ɐς�
			m_gameObjectListArray.at(prio).push_back(newObject);
			//FindGO�ׂ̈Ƀn�b�V�����쐬 hash�ɂ��Ă�Util.h���Q��
			unsigned int hash = MakeGameObjectNameKey(objectName);
			//IGameObject�ɐς܂�Ă���prio����������Ă���prio�ŏ�����
			newObject->m_priority = prio;
			//��Ɠ��������Ńn�b�V������
			newObject->m_nameKey = hash;
			return newObject;
		}
		/// <summary>
		/// �I�u�W�F�N�g�̍폜</para>
		/// </summary>
		void DeleteGameObject(IGameObject* gameObject)
		{
			if (gameObject != nullptr)
			{
				//���X�g�ɒǉ�
				m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
				gameObject = nullptr;
			}
		}
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�̌���
		/// </summary>
		template<class T>
		T* FindGameObject(const char* objectName, bool enableErrorMessage)
		{
			unsigned int nameKey = Util::MakeHash(objectName);
			//goList��m_gameObjectListArray��A��
			for (auto goList : m_gameObjectListArray) {
				//go��goList��
				for (auto go : goList) {
					//������
					if (go->m_nameKey == nameKey) {
						//�^�ϊ�
						T* p = dynamic_cast<T*>(go);
						//�^�ϊ��Ɏ��s
						if (p == nullptr && enableErrorMessage == true) {
							/*
							�����Ƀu���[�N�|�C���g��u���Ď~�܂����ꍇ��
							�^�ϊ���������FindGO�ł��ĂȂ��ꍇ������̂�
							�����ɓn�����N���X�̍Ċm�F�����Ă݂Ă��������B
							*/
						}
						//Find����
						return p;
					}
				}
			}
			if (enableErrorMessage == true) {
				/*
				�����Ƀu���[�N�|�C���g��u���Ď~�܂����ꍇ��
				FindGO�ɓn���ꂽ���O�����݂��Ȃ��Ƃ������ƂȂ̂�
				FindGO��NewGO�̃I�u�W�F�N�g�l�[�����Ċm�F���Ă݂Ă��������B
				*/
			}
			//������Ȃ�����
			return nullptr;
		}
		template<class T>
		void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
		{
			unsigned int nameKey = Util::MakeHash(objectName);
			for (auto goList : m_gameObjectListArray) {
				for (auto go : goList) {
					if (go->m_nameKey == nameKey) {
						//�������B
						T* p = dynamic_cast<T*>(go);
						if (func(p) == false) {
							//�N�G�����f�B
							return;
						}
					}
				}
			}
		}
	public:
		/*
		�����o�֐���`�ł��B
		������̏�����cpp�ɏ����Ă���܂�
		*/
		//������
		void Start();
		//�X�V
		void Update();
		//�`��
		void Draw();
		/// <summary>
		/// �����_�[�������Ă΂��O�ɌĂ΂��`�揈��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void ForwardRender(RenderContext& rc);
		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void PostRender(RenderContext& rc);
		/// <summary>
		/// �Q�[���I�u�W�F�N�g�}�l�[�W���[����Ă΂��e����
		/// </summary>
		void ExecuteFromGameThread();
		/// <summary>
		/// �I�u�W�F�N�g�̃f�[�^�[�J������
		/// </summary>
		/// <remarks>
		/// DeleteGO�͍폜���X�g�ɐς�ł邾������I
		/// �{���Ƀ������̉�������鏈���͂������I
		/// </remarks>
		void ExcuteDeleteGameObject();

	private:
		/*
		�����o�ϐ��ł�
		*/
		typedef std::list<IGameObject*>	GameObjectList;						//���O�ύX
		std::vector<GameObjectList>		m_gameObjectListArray;				//�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g		
		std::vector<GameObjectList>		m_deleteObjectArray[2];				//�폜����I�u�W�F�N�g�̃��X�g	�폜��������DeleteGO����΂��\�������邩��_�u���o�b�t�@��
		int								m_currentDeleteObjectBufferNo = 0;	//�폜���̃o�b�t�@�[�ԍ�

	};
	/*
	�֐������b�v���Ă��邾���ł�
	�����Œl�̏����������Ă��Ƃ������������œn���Ȃ��Ă��悭�Ȃ�܂��B
	*/
	/// <summary>
	/// �V���O���g�� �C���X�^���X�Ԃ��Ă�񂾂Ȓ��x�̗����ő������v
	/// <para>�Q�[���I�u�W�F�N�g�}�l�[�W���֘A�̊֐��Ăяo�������b�v����̂Ɏg���Ă�</para>
	/// </summary>
	/// <returns>�}�l�[�W���[�̃C���X�^���X</returns>
	static inline GameObjectManager& gameObjectManager()
	{
		return GameObjectManager::Instance();
	}
	/// <summary>
	/// <para>�I�u�W�F�N�g�̍쐬</para>
	/// <para>���̊֐��ō�����I�u�W�F�N�g��DeleteGO�ŏ�������</para>
	/// </summary>
	/// <remarks>
	/// DeleteGO�ŏ����Ȃ������ꍇ�́Am_gameObjectListArray����������Ă�
	/// </remarks>
	/// <typeparam name="T"><para>�V�������I�u�W�F�N�g</para></typeparam>
	/// <param name="prio">�D��x</param>
	/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
	/// <returns>�I�u�W�F�N�g</returns>
	template<class T>
	static inline T* NewGO(int priority, const char* objectName = nullptr)
	{
		return gameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
	}
	/// <summary>
	///	�Q�[���I�u�W�F�N�g�̕�������
	/// </summary>
	/// <param name="objectName">�I�u�W�F�N�g���O</param>
	/// <param name="enableErrorMessage">�G���[���b�Z�[�W�̕\��</param>
	template<class T>
	static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
	{
		return gameObjectManager().FindGameObjects<T>(objectName, func);
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̌��� �d����I
	/// <para>���G���[���b�Z�[�Wtrue�ɂ��Ă��o�Ȃ��̂Ł�</para>
	/// <para>���u���C�N�|�C���g�őΉ������肢���܂��B��</para>
	/// </summary>
	/// <typeparam name="T">�����������I�u�W�F�N�g</typeparam>
	/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
	/// <param name="enableErrorMessage">�G���[�\��</param>
	template<class T>
	static inline T* FindGO(const char* objectName, bool enableErrorMessage = true)
	{
		return gameObjectManager().FindGameObject<T>(objectName, enableErrorMessage);
	}

	/// <summary>
	/// �I�u�W�F�N�g�̍폜
	/// <para>�I�u�W�F�N�g���폜�\�胊�X�g�ɐς�</para>
	/// </summary>
	/// <remarks>
	/// ���ۂɂ͂����ŃI�u�W�F�N�g�������Ă���킯�ł͂���܂���B
	/// ���t���[��m_deleteObjectArray�ɐς܂�ĂȂ����m�F����
	/// ExecuteDeleteGameObjects�Ƃ����֐��ō폜�������s���܂�
	/// </remarks>
	///	<param name="IGameObject">���������I�u�W�F�N�g�̃N���X</param>
	static inline void DeleteGO(IGameObject* go)
	{
		gameObjectManager().DeleteGameObject(go);
	}

}

