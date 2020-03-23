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
		const State GetState() {
			return state;
		}
		const CVector3 GetPosition() {
			return *m_Position;
		}
		//Ž¥—Í‚Å“®‚¢‚Ä‚¢‚­•ûŒü‚ð‚Æ‚é
		const CVector3 GetMove() {
			return m_MagnetForce;
		}
		const void SetState(State s) {
			state = s;
		}
		const void SetPosition(CVector3* pos) {
			m_Position = pos;
		}
		void SetCool(float t) {
			CoolTime = t;
		}
	private:
		bool Start();
		void Update();
		void PostRender();
		State		state		  = NoMode;
		CQuaternion m_Rot		  = CQuaternion::Identity();
		//myEngine::SpriteRender* m_SMagSprite = nullptr;
		//myEngine::SpriteRender* m_NMagSprite = nullptr;
		CVector3*	m_Position	  = nullptr;
		CVector3	m_MagnetForce = CVector3::Zero();
		float		CoolTime	  = 100.0f;
		friend class MagnetManager;
	};
}