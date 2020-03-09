#pragma once

#include "graphics/2D/SpriteRender.h"
#include "GameObject/IGameObject.h"

namespace MyMagnet {
	class Magnet : public myEngine::IGameObject
	{
		CVector3* m_Position = nullptr;
		CVector3 m_MagnetForce = CVector3::Zero();
		friend class MagnetManager;
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
		void Update();
		void PostDraw();
		myEngine::SpriteRender* m_SMagSprite = nullptr;
		myEngine::SpriteRender* m_NMagSprite = nullptr;
		const CVector3 GetPosition() {
			return *m_Position;
		}
		const void SetPosition(CVector3* pos) {
			m_Position = pos;
		}
		//Ž¥—Í‚Å“®‚¢‚Ä‚¢‚­•ûŒü‚ð‚Æ‚é
		const CVector3 GetMove() {
			return m_MagnetForce;
		}
	private:
		State state = NoMode;
		CQuaternion m_Rot = CQuaternion::Identity();
		bool Start();
	public:
		const void SetState(State s) {
			state = s;
		}
		const State GetState() {
			return state;
		}
	};
}