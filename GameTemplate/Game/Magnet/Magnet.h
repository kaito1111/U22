#pragma once
#include "graphics/2D/SpriteRender.h"
namespace MyMagnet {
	class Magnet
	{
		CVector3* m_Position = nullptr;
		CVector3 m_Diff = CVector3::Zero();
		friend class MagnetManager;
	public:
		Magnet();
		~Magnet();
		CVector3 MagnetMove();
		enum State {
			NMode,
			SMode,
			NoMode,
			Num,
		};
		myEngine::SpriteRender* m_SMagSprite = nullptr;
		myEngine::SpriteRender* m_NMagSprite = nullptr;
	private:
		State state = NoMode;
	public:
		const void SetState(State s) {
			state = s;
		}
		const State GetState() {
			return state;
		}
		const CVector3 GetPosition() {
			return *m_Position;
		}
		const void SetPosition(CVector3* pos) {
			m_Position = pos;
		}
		//Ž¥—Í‚Å“®‚¢‚Ä‚¢‚­•ûŒü‚ð‚Æ‚é
		const CVector3 GetMove() {
			return m_Diff;
		}
	};
}