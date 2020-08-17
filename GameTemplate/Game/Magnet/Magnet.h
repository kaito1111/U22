#pragma once

#include "graphics/2D/SpriteRender.h"
#include "GameObject/IGameObject.h"

namespace MyMagnet {
	class Magnet : public myEngine::IGameObject
	{
	public:
		Magnet();
		~Magnet();
		CVector3 MagnetMove();
		enum State {
			NoMode,
			NMode,
			SMode,
			Num,
		};
		const State GetState() const
		{
			return state;
		}
		const CVector3 GetPosition() const
		{
			return *m_Position;
		}
		//���͂œ����Ă����������Ƃ�
		const CVector3 GetMove() const
		{
			return m_MagnetForce;
		}
		const void SetState(const State& s) {
			state = s;
		}
		void SetPosition(CVector3* pos) {
			m_Position = pos;
		}
		void SetChange(bool change)//�ύX�ł��邩��ݒ肷��
		{
			Change = change;
		}
		bool IsChenge() //�ύX�ł���H
		{
			return Change;
		}
	private:
		bool Start();
		void Update();
		void PostRender();
		State state		  = NoMode;
		CQuaternion m_Rot		  = CQuaternion::Identity();
		//myEngine::SpriteRender* m_SMagSprite = nullptr;
		//myEngine::SpriteRender* m_NMagSprite = nullptr;
		CVector3* m_Position	  = nullptr;
		CVector3 m_MagnetForce = CVector3::Zero();
		myEngine::Effect* SEffect = nullptr;
		myEngine::Effect* NEffect = nullptr;
		SoundSource m_Se;
		float SeVolume = 1.0f;
		friend class MagnetManager;
		bool Change = true;		//�ύX�ł��邩�B
	};
}