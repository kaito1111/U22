#pragma once

namespace myEngine {
	class SkinModelRender :public IGameObject
	{
	public:
		SkinModelRender() {};
		~SkinModelRender() {};

		void Init(wchar_t* filePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0);
		void IsPlayingAnimation(int animNo, float interpolateTime = 0.0f)
		{
			return m_animation.Play(animNo, interpolateTime);
		};

		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		};
		/*!
		*@brief	���W��ݒ�B
		*@details
		* 3D���f����\�����������[���h���W���w�肵�Ă��������B
		*@param[in]	position		���[���h���W�B
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/*!
		*@brief	��]��ݒ�B
		*@details
		* 3D���f���̃��[���h��Ԃł̉�]��\���A�N�H�[�^�j�I�����w�肵�Ă��������B
		*@param[in]	rotation		���[���h��Ԃł̉�]�N�H�[�^�j�I���B
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		/*!
		*@brief	�g�嗦��ݒ�B
		*@details
		* 3D���f���̃��[���h��Ԃł̊g�嗦���w�肵�Ă��������B
		*@param[in] scale			���[���h��Ԃł̊g�嗦�B( 1, 1, 1 )�œ��{�B
		*/
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/*!
		*@brief	���[���h��Ԃł̍��W�A��]�A�g������ׂĐݒ�
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in] scale		�g��B
		*/
		void SetPRS(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
		{
			SetPosition(trans);
			SetRotation(rot);
			SetScale(scale);
		}
		/*!
		*@brief	�X�L�����f���擾�B
		*@return	�X�L�����f���B
		*/
		SkinModel& GetSkinModel()
		{
			return m_skinModel;
		}
		/*!
		*@brief	�X�L�����f���擾�Bconst�Q�ƔŁB
		*@return	�X�L�����f���B
		*/
		const SkinModel& GetSkinModel() const
		{
			return m_skinModel;
		}
		/*!
		*@brief	�A�j���[�V�����̍X�V�t���O��ݒ�B
		*@param flag	�X�V�t���O
		*@details
		*���̃t���O��false��ݒ肷��ƁA�A�j���[�V�����̍Đ����~�܂�܂��B
		*/
		void SetUpdateAnimationFlag(bool flag)
		{
			m_isUpdateAnimation = flag;
		}
		/*!
		* @brief	�A�j���[�V�����̏������B
		*/
		void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

		void SetSilhouette(const int lview)
		{
			Silhouette = lview;
		}
	private:
		/*!
		* @brief	�X�V�O�ɌĂ΂��֐��B
		*/
		bool Start() override final;
		/*!
		* @brief	�X�V�B
		*/
		void Update() override final;
		void Draw()override;
	private:
		AnimationClip* m_animationClips = nullptr;
		int m_numAnimationClips = 0;
		CVector3 m_position = CVector3::Zero();
		CQuaternion m_rotation = CQuaternion::Identity();
		CVector3 m_scale = CVector3::One();
		Animation m_animation;
		SkinModel m_skinModel;
		//CSkinModelData				m_skinModelData;												�����ł��ĂȂ�
		const std::wstring m_filePath;
		//bool						m_isFrustumCulling = false;			//!<�t���X�^���J�����O���s���H	�����ł��ĂȂ�
		//CObjectFrustumCulling		m_frustumCulling;					//!<�t���X�^���J�����O�B		�����ł��ĂȂ�
		bool m_isUpdateAnimation = true;
		int Silhouette = 0;
	};
}