#pragma once
/// <summary>
/// �Q�[���I�u�W�F�N�g�̊��N���X
/// �I�u�W�F�N�g�}�l�[�W���[�̊֐����g���ꍇ�͌p�����ĂˁI�I
/// </summary>


namespace myEngine {
	class GameObjectManager;
	//���O�ύX�����Ă邾��
	typedef unsigned char	GameObjPrio;
	class IGameObject
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false)
		{
		};
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		/// <remarks>
		/// virtual�͒�`���Ă邾���ł��A�����͔h���N���X�ɏ����Ă�������
		/// </remarks>
		virtual ~IGameObject()
		{
		};
		/// <summary>
		/// <para>Update�̒��O�ɌĂ΂��J�n����</para>
		/// <para>true���Ԃ����ƍX�V����(Update)���J�n������</para>
		/// </summary>
		/// <returns>
		/// �I�u�W�F�N�g�̏�����1�t���[���łł���Ȃ�true�A�ł��Ă��Ȃ��Ȃ�false
		/// </returns>
		virtual bool Start() { return true; }
		/// <summary>
		/// �X�V����
		/// </summary>
		void Update() {};
		/// <summary>
		/// �`�揈��
		/// </summary>
		virtual void Draw() {};
		/// <summary>
		/// <para>���s�D��x���擾</para>
		/// </summary>
		/// <returns>
		/// �D��x
		/// </returns>
		GameObjPrio GetPriority() const
		{
			return m_priority;
		}

		friend class CGameObjectManager;
	protected:
		GameObjPrio		m_priority;		//�D��x
		bool			m_isStart;		//Start�t���O
		bool			m_isDead;		//���S�t���O
		bool			m_isActive;		//Active�t���O
		unsigned int	m_tags = 0;		//�^�O
		unsigned int	m_nameKey = 0;	//���O�L�[
	};
}


