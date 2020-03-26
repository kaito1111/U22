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
		*@brief	座標を設定。
		*@details
		* 3Dモデルを表示したいワールド座標を指定してください。
		*@param[in]	position		ワールド座標。
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/*!
		*@brief	回転を設定。
		*@details
		* 3Dモデルのワールド空間での回転を表す、クォータニオンを指定してください。
		*@param[in]	rotation		ワールド空間での回転クォータニオン。
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		/*!
		*@brief	拡大率を設定。
		*@details
		* 3Dモデルのワールド空間での拡大率を指定してください。
		*@param[in] scale			ワールド空間での拡大率。( 1, 1, 1 )で等倍。
		*/
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/*!
		*@brief	ワールド空間での座標、回転、拡大をすべて設定
		*@param[in]	pos			座標。
		*@param[in]	rot			回転。
		*@param[in] scale		拡大。
		*/
		void SetPRS(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
		{
			SetPosition(trans);
			SetRotation(rot);
			SetScale(scale);
		}
		/*!
		*@brief	スキンモデル取得。
		*@return	スキンモデル。
		*/
		SkinModel& GetSkinModel()
		{
			return m_skinModel;
		}
		/*!
		*@brief	スキンモデル取得。const参照版。
		*@return	スキンモデル。
		*/
		const SkinModel& GetSkinModel() const
		{
			return m_skinModel;
		}
		/*!
		*@brief	アニメーションの更新フラグを設定。
		*@param flag	更新フラグ
		*@details
		*このフラグにfalseを設定すると、アニメーションの再生が止まります。
		*/
		void SetUpdateAnimationFlag(bool flag)
		{
			m_isUpdateAnimation = flag;
		}
		/*!
		* @brief	アニメーションの初期化。
		*/
		void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

		void SetSilhouette(const int lview)
		{
			Silhouette = lview;
		}
	private:
		/*!
		* @brief	更新前に呼ばれる関数。
		*/
		bool Start() override final;
		/*!
		* @brief	更新。
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
		//CSkinModelData				m_skinModelData;												実装できてない
		const std::wstring m_filePath;
		//bool						m_isFrustumCulling = false;			//!<フラスタムカリングを行う？	実装できてない
		//CObjectFrustumCulling		m_frustumCulling;					//!<フラスタムカリング。		実装できてない
		bool m_isUpdateAnimation = true;
		int Silhouette = 0;
	};
}